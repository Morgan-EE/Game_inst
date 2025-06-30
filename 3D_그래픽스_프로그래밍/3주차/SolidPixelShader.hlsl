#include "Shared.fxh"

//--------------------------------------------------------------------------------------
// PSSolid - render a solid color
//--------------------------------------------------------------------------------------
// texture, sampler 
Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);


float4 PS(PS_INPUT input) : SV_Target
{
    float4 OutputColor = texture0.Sample(sampler0, input.UV);
    float4 finalColor = float4(input.diffuse, 1.f) * OutputColor;
	
    return finalColor;
}

//float4 main(PS_INPUT input) : SV_Target
//{
//    return txDiffuse.Sample(samLinear, input.UV);
//}
//float4 main(PS_INPUT input) : SV_TARGET
//{
//    return float4(txDiffuse.Sample(samLinear, input.Tex) * float4(input.Norm, 0));
//    //return vOutputColor;
//}

//PS_INPUT main(VS_INPUT input)
//{
//    PS_INPUT output = (PS_INPUT) 0;
//    output.Pos = mul(input.Pos, World);
    
//    //output.WldPos = output.Pos;
    
//    output.Pos = mul(output.Pos, View);
//    output.Pos = mul(output.Pos, Projection);
    
//    output.Norm = mul(float4(input.Norm, 1), World).xyz;
    
//    //float3 LightDir = normalize(vLightDir.xyz);
    
//    //float3 worldNormal = mul(input.Norm, (float3x3) World);
//    //worldNormal = normalize(worldNormal);
    
//    //output.Norm = dot(LightDir, worldNormal) * vLightColor.xyz;
//    //output.Tex = input.Tex;
    
//    return output;
//}