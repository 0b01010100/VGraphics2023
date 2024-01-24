struct VSInput
{
    float3 pos : SV_POSITION;
    float3 col : COLOR;
};
struct outPSIn
{
    float3 col : COLOR;
};
void vsmain(in VSInput input, out outPSIn output)
{
    output.col = input.col;

}