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
//Vertex shaders a responsilbe for processing each vertex before it is reasterized or put on the screen, They handle positioning and color of a vertex.
Output vsmain(input input)
{
    Output output = (Output)0;
    output.color = float3(input.color);
    output.pos = float4(input.pos, 1.f);

    return output;
}