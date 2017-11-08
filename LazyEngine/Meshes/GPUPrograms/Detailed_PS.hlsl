Texture2D shaderTexture : register(t0);
Texture2D bumpMapTexture : register(t1); 
SamplerState SampleType : register(s0);

struct PS_INPUT
{
	float4 Position : SV_POSITION; // Vertex shaders must output SV_POSITION
	float3 Normal : NORMAL;
	float3 PositionL : POSITION;
	float2 TexCoord : TEXCOORD;
};

struct PS_OUTPUT
{
	float4 RGBColor : SV_TARGET;  // pixel color (your PS computes this system value)
};
float3 LightRender(float3 normal,float3 eyePos,float3 lightDirection,float spec,float3 posL,float3 diffuseColor){
	
	lightDirection = normalize(lightDirection);
	float4 lightColor = float4(1.0,1.0,1.0,1.0);
	
	normal = normalize(normal);
	float diffuseFactor = dot(normal,lightDirection);
	float3 reflection = 2*dot(lightDirection,normal)*normal-lightDirection;
	float3 viewDirection = (eyePos - posL);
	viewDirection = normalize(viewDirection);
	float specFactor = pow(max(dot(viewDirection,reflection),0.0),spec);
	
	float3 litColor = diffuseColor;
	
	litColor += diffuseFactor * diffuseColor;
	litColor += specFactor * lightColor.xyz;
	return litColor;
}
PS_OUTPUT main(PS_INPUT In)
{
	PS_OUTPUT Output;
	//Temp light info will come from LightObject afterwards
	
	float4 finalColor = float4(0, 0, 0, 1.0);
	float4 textureColor = shaderTexture.Sample(SampleType,In.TexCoord);
	float3 litColor = LightRender(In.Normal, float3(0.0f, 0.0f, 6.5f), float3(-1.0, 0.0, 1.0), 2.0, In.PositionL, textureColor.xyz);
	finalColor += float4(litColor,0.0);
	Output.RGBColor = finalColor;
	
	return Output;
}


// You can return a float4 (instead of a struct) by applying the semantic like so.
/*
float4 main(PS_INPUT In) : SV_TARGET
{
return In.Color;
}*/