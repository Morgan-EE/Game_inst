#include "Shared.fxh"

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;

    // 정점 좌표계 변환
    float4 pos = input.Pos;

    pos = mul(pos, World);
    output.PosWorld = pos.xyz; // 투영 변환 하기 전 월드 위치 저장

    pos = mul(pos, View);
    pos = mul(pos, Projection);
    output.PosProjection = pos; // 투영 변환 후 위치

    // 텍스처 로드
    output.Texcoord = input.Tex;

    // 물체의 노멀벡터를 월드좌표계의 행렬로 변환한 후 노멀라이즈
    // 스케일 변환에 영향을 받지 않는 노멀 벡터를 구하기 위함 (노말 벡터도 함께 변환됨)
    output.NorWorld = normalize(mul(input.Nor, (float3x3) World));

    return output;
}