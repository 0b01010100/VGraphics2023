struct input
{
    float3 position : POSITION;
    float3 color : COLOR;
};
struct Output
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};
cbuffer constant : register(b0)
{
    row_major float3x3 m_world;

}
//Vertex shaders a responsilbe for processing each vertex before it is reasterized or put on the screen, They handle positioning and color of a vertex.
Output vsmain(input input)
{
    
    Output output = (Output) 0;
    output.position = float4(mul(input.position, m_world), 1.f);
    output.color = input.color;
    return output;
}