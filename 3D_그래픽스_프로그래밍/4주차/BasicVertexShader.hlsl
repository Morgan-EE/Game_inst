#include "Shared.fxh"

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;

    // ���� ��ǥ�� ��ȯ
    float4 pos = input.Pos;

    pos = mul(pos, World);
    output.PosWorld = pos.xyz; // ���� ��ȯ �ϱ� �� ���� ��ġ ����

    pos = mul(pos, View);
    pos = mul(pos, Projection);
    output.PosProjection = pos; // ���� ��ȯ �� ��ġ

    // �ؽ�ó �ε�
    output.Texcoord = input.Tex;

    // ��ü�� ��ֺ��͸� ������ǥ���� ��ķ� ��ȯ�� �� ��ֶ�����
    // ������ ��ȯ�� ������ ���� �ʴ� ��� ���͸� ���ϱ� ���� (�븻 ���͵� �Բ� ��ȯ��)
    output.NorWorld = normalize(mul(input.Nor, (float3x3) World));

    return output;
}