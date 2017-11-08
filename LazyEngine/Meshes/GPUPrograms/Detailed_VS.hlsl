cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix mWorld;       // world matrix for object
	matrix View;        // view matrix
	matrix Projection;  // projection matrix
	float3 color;
	float alpha;
};

struct VS_INPUT
{
	float3 vPos   : POSITION;
	float2 vTexCoord : TEXCOORD;
	float3 vNormal : NORMAL;
	float3 vTangent : NORMAL;
};

struct VS_OUTPUT
{
	float4 Position : SV_POSITION; // Vertex shaders must output SV_POSITION
	float3 Normal : NORMAL;
	float3 PositionL : POSITION;
	float2 TexCoord : TEXCOORD;
};

VS_OUTPUT main(VS_INPUT input) // main is the default function name
{
	VS_OUTPUT Output;

	float4 pos = float4(input.vPos, 1.0f);
	float3 posL  = input.vPos;
	float4 normal = float4(input.vNormal,0.0f);
	// Transform the position from object space to homogeneous projection space
	pos = mul(mWorld,pos);
	posL =  pos.xyz;
	pos = mul(View, pos);
	pos = mul(Projection, pos);
	normal = mul(mWorld,normal);
	
	Output.Position = pos;
	Output.Normal = normal.xyz;
	Output.PositionL = posL;
	Output.TexCoord = input.vTexCoord;
	// Just pass through the color data
	

	return Output;
}