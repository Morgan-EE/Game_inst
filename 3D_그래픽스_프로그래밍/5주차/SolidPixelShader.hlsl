#include "Shared.fxh"

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(PS_INPUT input) : SV_Target
{
    // 물체로부터 뻗어나가는 노멀 방향만 남기기 위해 노멀라이즈
    float3 vNormal = normalize(input.NorWorld);
    float3 vTangent = normalize(input.TangentWorld);
    float3 vBiTangent = cross(vNormal, vTangent);
    
    if(UseNormalMap)
    {
        float3 vNormalTangentSpace = txNormal.Sample(samLinear, input.Texcoord).rgb * 2.0f - 1.0f;
        float3x3 WorldTransform = float3x3(vTangent, vBiTangent, vNormal);
        vNormal = mul(vNormalTangentSpace, WorldTransform);
        vNormal = normalize(vNormal);
    }
    
    // 텍스처
    float4 Texture = txDiffuse.Sample(samLinear, input.Texcoord);
    // 모든 물체에 적용하는 바탕 색 * 물체가 Ambient를 조절하는 색
    // 빛의 방향만 남기기 위해 노멀라이즈
    float fNDotL = max(dot(vNormal, -LightDirection), 0);
    float3 LightVector = normalize(LightDirection.xyz);
    // 내 시선 끝의 물체 픽셀로부터 카메라를 바라보는 방향만 남기기 위해 노멀라이즈
    float3 ViewVector = normalize(EyePosition - input.PosWorld);
    float4 Ambient = LightAmbient * MaterialAmbient * Texture * 0.1f;
    
    float4 DiffuseColor = LightDiffuse * MaterialDiffuse * Texture * fNDotL; //* Texture * fNDotL; //0.1f * fNDotL;
    //float4 DiffuseColor = dot(vNormal, -LightVector) * Diffuse;
    
    // 방향이 다른 두 벡터(Normal, vLightDirection)을 내적하면 음수가 도출된다.
    // 따라서 부호를 맞춰주기 위해 vLightDirection에 -를 곱해준다.
    
    float4 Diffuse = dot(vNormal, -LightVector) * DiffuseColor;
    //float4 Diffuse = LightDiffuse * MaterialDiffuse * 0.1f * fNDotL; //* Texture * fNDotL; //0.1f * fNDotL;

    // Specular Light
    float4 Specular;
    
    if (!UseBlinnPhong)
    {
        // Phong (반사벡터를 구해야해서 계산량 많음)
        float3 ReflectionVector = reflect(LightVector, vNormal);

        // 빛과 시선벡터의 내적(각도)에 따라 점의 색상이 밝아지도록 함
        float fRDotV = max(0.0f, dot(ReflectionVector, ViewVector));
        float4 Phong = pow(fRDotV, MaterialSpecularPower) * saturate(MaterialSpecular) * saturate(LightSpecular);
        Specular = Phong;
    }
    else
    {
        // Blinn Phong (계산량이 줄어들고 간단해진다)
        float3 HalfVector = normalize(-LightVector + ViewVector);

        // 물체의 법선 벡터와 하프 벡터의 내적으로 대체한다
        float fHDotN = max(0.0f, dot(HalfVector, vNormal));
        float4 BlinnPhong = pow(fHDotN, MaterialSpecularPower) * MaterialSpecular * LightSpecular;
        Specular = BlinnPhong;
    }
    
    Specular *= pow(max(0.0f, dot(normalize(-LightVector + ViewVector), vNormal)), MaterialSpecularPower) * MaterialSpecular * LightSpecular;
    if (UseSpecularMap)
    {
        Specular *= txSpecular.Sample(samLinear, input.Texcoord);
    }
    
    
    // 구성요소를 곱하면 값이 조절되는 것이지 합쳐지지 않음
    // 따라서 곱셈이 아닌 덧셈으로 각 구성요소를 결합함
    return saturate(Ambient + Diffuse + Specular);
}