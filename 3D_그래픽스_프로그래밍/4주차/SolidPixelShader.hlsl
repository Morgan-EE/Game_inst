#include "Shared.fxh"

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(PS_INPUT input) : SV_Target
{
    // ��ü�κ��� ������� ��� ���⸸ ����� ���� ��ֶ�����
    float3 NormalVector = normalize(input.NorWorld);

    // ���� ���⸸ ����� ���� ��ֶ�����
    float3 LightVector = normalize(LightDirection.xyz);

    // �� �ü� ���� ��ü �ȼ��κ��� ī�޶� �ٶ󺸴� ���⸸ ����� ���� ��ֶ�����
    float3 ViewVector = normalize(EyePosition - input.PosWorld);

    // ��� ��ü�� �����ϴ� ���� �� * ��ü�� Ambient�� �����ϴ� ��
    float4 Ambient = LightAmbient * MaterialAmbient * 0.1f;

    // �ؽ�ó
    float4 Texture = txDiffuse.Sample(samLinear, input.Texcoord);

    // Diffuse Light(=Lambertian Lighting)
    float4 DiffuseColor = LightDiffuse * MaterialDiffuse * Texture;

    // ������ �ٸ� �� ����(Normal, vLightDirection)�� �����ϸ� ������ ����ȴ�.
    // ���� ��ȣ�� �����ֱ� ���� vLightDirection�� -�� �����ش�.
    float4 Diffuse = dot(NormalVector, -LightVector) * DiffuseColor;

    // Specular Light
    float4 Specular;
    if (!UseBlinnPhong)
    {
        // Phong (�ݻ纤�͸� ���ؾ��ؼ� ��귮 ����)
        float3 ReflectionVector = reflect(LightVector, NormalVector);

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
        float fHDotN = max(0.0f, dot(HalfVector, NormalVector));
        float4 BlinnPhong = pow(fHDotN, MaterialSpecularPower) * MaterialSpecular * LightSpecular;
        Specular = BlinnPhong;
    }

    // ������Ҹ� ���ϸ� ���� �����Ǵ� ������ �������� ����
    // ���� ������ �ƴ� �������� �� ������Ҹ� ������
    return saturate(Ambient + Diffuse + Specular);
}