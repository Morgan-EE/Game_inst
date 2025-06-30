#include "Shared.fxh"

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

// IA - VS - RS - PS - OM
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output;
    output.Pos = mul(input.Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    float3 normal = mul(input.Norm, (float3x3) World);
    normal = normalize(normal);
    output.diffuse = saturate(dot(normal, (float3) -vLightDir)) * vLightColor;
    output.UV = input.UV;

    return output;
}

//VS_OUTPUT VS(VS_INPUT input)
//{
//    VS_OUTPUT output;

//    float4x4 WVP = mul(mul(World, View), Projection);
    
//    output.Pos = mul(input.Pos, WVP);
//    output.UV = input.UV;
//    output.Color = input.Color;
//    output.Norm = normalize(mul(input.Norm, (float3x3) World));

//    return output;
//}


