Texture2D DiffuseTexture : register(t0);
Texture2D NormalTexture : register(t1);
Texture2D SpecularTexture : register(t2);

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
	float2 TexCoord : TEXCOORD;
};

struct PS_OUTPUT
{
	float4 LightPass : SV_TARGET3;
};

float4 LightRenderDirectional(float3 normal, float3 eyePos, float3 lightDirection, float spec, float3 posL, float4 diffuseColor ,float4 SpecularColor) {

	lightDirection = normalize(-lightDirection);
	float4 ambient = float4(0.5, 0.5, 0.5, 1.0f);
	float4 lightColor = float4(0.1, 0.0, 0.1, 1.0);
	float4 specColor = float4(0.1, 0.1, 0.1, 1.0);
	specColor *= SpecularColor;
	normal = normalize(normal);
	float diffuseFactor = dot(normal, lightDirection);
	float3 reflection = 2 * dot(lightDirection, normal)*normal - lightDirection;
	float3 viewDirection = (eyePos - posL);
	viewDirection = normalize(viewDirection);
	float specFactor = pow(max(dot(viewDirection, reflection), 0.0), spec);

	float4 litColor = float4(0.1, 0.1, 0.1, 1.0);

	litColor += diffuseFactor * diffuseColor;
	float len = length(litColor);
	litColor += specFactor *specColor* lightColor *len;
	litColor.w = 1.0f;
	return litColor;
	
}

PS_OUTPUT main(PS_INPUT In) {

	PS_OUTPUT output;
	float4 Diffuse = DiffuseTexture.Sample(SampleType, In.TexCoord);
	float4 Normal = NormalTexture.Sample(SampleType, In.TexCoord);
	float4 Specular = SpecularTexture.Sample(SampleType, In.TexCoord);

	float4 finalColor;
	float4 litColor = LightRenderDirectional(Normal.xyz,eyePos.xyz,float3(-1.0f,-1.0f,0.0f), 16.0f, In.Position.xyz, Diffuse,Specular);
	if (toggles_ADNS[0] > 0.1f)
	{
		output.LightPass = litColor;
	}
	else if (toggles_ADNS[1] > 0.1f)
	{
		output.LightPass = Diffuse;
	}
	else if (toggles_ADNS[2] > 0.1f)
	{
		output.LightPass = Normal;
	}
	else if (toggles_ADNS[3] > 0.1f)
	{
		output.LightPass = Specular;
	}
	return output;

}