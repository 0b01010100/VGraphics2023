struct outPSIn
{
    float4 pos : SV_POSITION;
    float3 col : COLOR;
};
cbuffer c0 : register(b0)
{
    float2 iResolution;
};
cbuffer c1 : register(b1)
{
    float3 pos;
};
float4 psmain(outPSIn input) : SV_TARGET
{
    float2 uv = (input.pos.xy / iResolution.xy - 0.5) * 2.0f;
    uv.y *= -1;
    uv.x *= iResolution.x / iResolution.y;
    float d = sin(length(uv) );


    return float4(dot(d, uv.x - uv.y), rcp(cosh(uv - 2)).x, d, 1.0f);
}