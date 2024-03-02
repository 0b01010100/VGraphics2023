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

//Vertex shaders a responsilbe for processing each vertex before it is reasterized or put on the screen, They handle positioning and color of a vertex.
Output vsmain(input input)
{
    
    Output output = (Output)0;
    
    return output;
}