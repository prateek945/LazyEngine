Texture2D shaderTexture : register(t0);
Texture2D bumpMapTexture : register(t1);
Texture2D specularTexture : register(t2);

SamplerState SampleType : register(s0);

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
struct PS_INPUT
{
	float4 Position : SV_POSITION; // Vertex shaders must output SV_POSITION
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 PositionL : POSITION;
	float2 TexCoord : TEXCOORD;
};

struct PS_OUTPUT
{
	float4 Diffuse : SV_TARGET0;
	float4 Normal : SV_TARGET1;
	float4 Specular : SV_TARGET2;
	
};

PS_OUTPUT main(PS_INPUT In)
{
	PS_OUTPUT Output;
	//Temp light info will come from LightObject afterwards
	
	float4 finalColor = float4(0, 0, 0, 0.0);
	float4 textureColor = shaderTexture.Sample(SampleType,In.TexCoord);
	float3 perPixelNormal = In.Normal;
	float4 perPixelSpecular = float4(1.0f, 1.0f, 1.0f, 1.0f);
	if (detailedMesh.x > 0.1f) {
		// retrieve the normal vector from bump map
		perPixelNormal = bumpMapTexture.SampleLevel(SampleType,In.TexCoord,0).xyz;


		//Uncompress from [0,1] to [-1,1]
		perPixelNormal = 2.0*perPixelNormal - 1.0;

		//Build orthonormal basis
		float3 N = normalize(In.Normal);
		float3 T = normalize(In.Tangent - dot(In.Tangent, N)*N);
		float3 B = cross(N, T);

		float3x3 TBN = float3x3(T, B, N);

		// Tranform from tangent space to world space
		perPixelNormal = normalize(mul(perPixelNormal, TBN));
	}
	else
	{
		perPixelNormal =  normalize(perPixelNormal);
	}

	if(detailedMesh.y > 0.1f)
	{ 
		perPixelSpecular = specularTexture.Sample(SampleType, In.TexCoord);
	}
	Output.Diffuse = textureColor;
	Output.Normal = float4(perPixelNormal, 1.0f);
	Output.Specular =perPixelSpecular;
	
	return Output;
}


// You can return a float4 (instead of a struct) by applying the semantic like so.
/*
float4 main(PS_INPUT In) : SV_TARGET
{
return In.Color;
}*/