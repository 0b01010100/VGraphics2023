struct VSInput
{
    float3 pos : POSITION;
    float3 col : COLOR;
};
struct outPSIn
{
    float4 pos : SV_POSITION;
    float3 col : COLOR;
};

outPSIn vsmain(VSInput input)
{
    outPSIn output = (outPSIn) 0;
    output.col = input.col;
    output.pos = float4(input.pos, 1.f);
    return output;

}