struct Output
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;

};
cbuffer constData : register(b0)
{
    float x;
    float y;
    float z;
}
//The Shader/Pixel shader handles the color calculations for each pixel on the screen by
//taking some data from the Vetex shader. 
float4 psmain(Output input) : SV_Target
//SV_Taget tells us that the ouput will be stored in the first render target by native grahicp pipline/Ouput Merger stage
{
    
    return float4(input.color, 1);
}