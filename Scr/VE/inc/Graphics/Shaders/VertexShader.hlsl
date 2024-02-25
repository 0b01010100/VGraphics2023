struct input
{
    float3 pos : POSITION;
    float3 color : COLOR;
};
struct Output
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
};
struct Matrix2x2
{
    float a, b, c, d;
};
cbuffer constant : register(b0)
{
    Matrix2x2 jj;
    float3 pos;
}
//Vertex shaders a responsilbe for processing each vertex before it is reasterized or put on the screen, They handle positioning and color of a vertex.
Output vsmain(input input)
{
    
    Output output = (Output)0;
    float2x2 j = float2x2(jj.a, jj.b, jj.c, jj.d);
    output.pos = float4(mul(input.pos.xy, j), 1, 1.f);
    
    output.color = float3(input.color);
    return output;
}