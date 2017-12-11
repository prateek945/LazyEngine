cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix mWorld;       // world matrix for object
	matrix View;        // view matrix
	matrix Projection;  // projection matrix
	float3 color;
	float alpha;
	float4 eyePos;
	float4 detailedMesh;
};

struct VS_INPUT
{
	float3 vPos   : POSITION;
	float2 vTexCoord : TEXCOORD;
	float3 vNormal : NORMAL;
	float3 vTangent : TANGENT;
};

struct VS_OUTPUT
{
	float4 Position : SV_POSITION; // Vertex shaders must output SV_POSITION
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 PositionL : POSITION;
	float2 TexCoord : TEXCOORD;
};

VS_OUTPUT main(VS_INPUT input) // main is the default function name
{
	VS_OUTPUT Output;

	float4 pos = float4(input.vPos, 1.0f);
	float3 posL  = input.vPos;
	float4 normal = float4(input.vNormal,0.0f);
	float4 tangent = float4(input.vTangent, 0.0f);
	// Transform the position from object space to homogeneous projection space
	//pos = mul(mWorld,pos);
	posL =  mul(pos,mWorld).xyz;
	float4x4 mWorldViewProjection = mul(mWorld, mul(View, Projection));
	pos = mul(pos, mWorldViewProjection);
	normal = mul(normal,mWorld);
	tangent = mul(tangent,mWorld);
	Output.Position = pos;
	Output.Normal = normal.xyz;
	Output.PositionL = posL;
	Output.TexCoord = input.vTexCoord;
	Output.Tangent = tangent.xyz;
	// Just pass through the color data
	

	return Output;
}