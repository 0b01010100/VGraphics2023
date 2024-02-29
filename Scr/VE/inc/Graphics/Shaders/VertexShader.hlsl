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
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
  
    unsigned int m_time;
}
//Vertex shaders a responsilbe for processing each vertex before it is reasterized or put on the screen, 
//They handle positioning and color of a vertex.
Output vsmain(input input)
{
    
    Output output = (Output)0;
    float4 pos = float4(input.position, 1.f);
	//WORLD SPACE
    output.position = mul(pos, m_world);
	//VIEW SPACE
    output.position = mul(output.position, m_view);
	//SCREEN SPACE
    output.position = mul(output.position, m_proj);
    output.color = input.color;
    return output;
}