cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix mWorld;       // world matrix for object
	matrix View;        // view matrix
	matrix Projection;  // projection matrix
	float3 color;
	float alpha;
	float4 eyePos;
	float4 detailedMesh;
	float4 toggles_ADNS;
};

struct VS_INPUT
{
	float3 vPos   : POSITION;
	float2 vTexCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Position : SV_POSITION; // Vertex shaders must output SV_POSITION
	float2 TexCoord : TEXCOORD;
};

VS_OUTPUT main(VS_INPUT input,uint vI : SV_VERTEXID) // main is the default function name
{
	VS_OUTPUT Output;

	
	float2 texcoord = float2(vI & 1, vI >> 1); //you can use these for texture coordinates later
	Output.Position =  float4((texcoord.x - 0.5f) * 2, -(texcoord.y - 0.5f) * 2, 0, 1);
	Output.TexCoord = texcoord;

	return Output;
}