#include "Shared.fxh"

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(PS_INPUT input) : SV_Target
{
    // ��ü�κ��� ������� ��� ���⸸ ����� ���� ��ֶ�����
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
    
    // �ؽ�ó
    float4 Texture = txDiffuse.Sample(samLinear, input.Texcoord);
    // ��� ��ü�� �����ϴ� ���� �� * ��ü�� Ambient�� �����ϴ� ��
    // ���� ���⸸ ����� ���� ��ֶ�����
    float fNDotL = max(dot(vNormal, -LightDirection), 0);
    float3 LightVector = normalize(LightDirection.xyz);
    // �� �ü� ���� ��ü �ȼ��κ��� ī�޶� �ٶ󺸴� ���⸸ ����� ���� ��ֶ�����
    float3 ViewVector = normalize(EyePosition - input.PosWorld);
    float4 Ambient = LightAmbient * MaterialAmbient * Texture * 0.1f;
    
    float4 DiffuseColor = LightDiffuse * MaterialDiffuse * Texture * fNDotL; //* Texture * fNDotL; //0.1f * fNDotL;
    //float4 DiffuseColor = dot(vNormal, -LightVector) * Diffuse;
    
    // ������ �ٸ� �� ����(Normal, vLightDirection)�� �����ϸ� ������ ����ȴ�.
    // ���� ��ȣ�� �����ֱ� ���� vLightDirection�� -�� �����ش�.
    
    float4 Diffuse = dot(vNormal, -LightVector) * DiffuseColor;
    //float4 Diffuse = LightDiffuse * MaterialDiffuse * 0.1f * fNDotL; //* Texture * fNDotL; //0.1f * fNDotL;

    // Specular Light
    float4 Specular;
    
    if (!UseBlinnPhong)
    {
        // Phong (�ݻ纤�͸� ���ؾ��ؼ� ��귮 ����)
        float3 ReflectionVector = reflect(LightVector, vNormal);

        // ���� �ü������� ����(����)�� ���� ���� ������ ��������� ��
        float fRDotV = max(0.0f, dot(ReflectionVector, ViewVector));
        float4 Phong = pow(fRDotV, MaterialSpecularPower) * saturate(MaterialSpecular) * saturate(LightSpecular);
        Specular = Phong;
    }
    else
    {
        // Blinn Phong (��귮�� �پ��� ����������)
        float3 HalfVector = normalize(-LightVector + ViewVector);

        // ��ü�� ���� ���Ϳ� ���� ������ �������� ��ü�Ѵ�
        float fHDotN = max(0.0f, dot(HalfVector, vNormal));
        float4 BlinnPhong = pow(fHDotN, MaterialSpecularPower) * MaterialSpecular * LightSpecular;
        Specular = BlinnPhong;
    }
    
    Specular *= pow(max(0.0f, dot(normalize(-LightVector + ViewVector), vNormal)), MaterialSpecularPower) * MaterialSpecular * LightSpecular;
    if (UseSpecularMap)
    {
        Specular *= txSpecular.Sample(samLinear, input.Texcoord);
    }
    
    
    // ������Ҹ� ���ϸ� ���� �����Ǵ� ������ �������� ����
    // ���� ������ �ƴ� �������� �� ������Ҹ� ������
    return saturate(Ambient + Diffuse + Specular);
}