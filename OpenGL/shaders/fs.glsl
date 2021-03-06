#version 330

in vec4 v_col;
in vec2 v_tex_coord;
in vec3 v_normal;
in vec3 v_frag_pos;

out vec4 color;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

/* Base struct for the lights*/
struct Light
{
    vec3 color;
    float ambient_intensity;
    float diffuse_intensity;
};

struct DirectionLight
{
    /* Instances a Light struct. Acts like a 
     * superclass*/
    Light base;
    vec3 direction;
};

struct PointLight
{
    /* Instances a Light struct. Acts like a 
     * superclass*/
    Light base;
    vec3 position;
    float constant;
    float linear;
    float exponent;
};

struct SpotLight
{
    PointLight base;
    vec3 direction;
    float edge;
};

struct Material
{
    float specular_intensity;
    float shininess;
};

uniform int point_light_count;
uniform int spot_light_count;

uniform DirectionLight directional_light;
uniform PointLight point_lights[MAX_POINT_LIGHTS];
uniform SpotLight spot_lights[MAX_SPOT_LIGHTS];

uniform sampler2D the_texture;
uniform Material material;

/* Camera position*/
uniform vec3 eye_position;

/* Not the directional light. Utility for types of
 * light which uses direction to calculate its value.
 * Directional lights are fully calculated by directions.
 * Point lights are partially calculated by directions*/
vec4 CalculateLightByDirection(Light light, vec3 direction)
{
        /* Calculates the factor wich multiplies
     * the final color of the shader*/
    vec4 ambient_color = vec4(light.color, 1.0f) * light.ambient_intensity;

    /* The cosine of the angle between two 
     * vectors: dot product of two normalized 
     * vectors*/
    float diffuse_factor = max(dot(normalize(v_normal), normalize(direction)), 0.0f);

    /* How bright the diffuse lgiht should be*/
    vec4 diffuse_color = vec4(light.color, 1.0f) * light.diffuse_intensity * diffuse_factor;

    vec4 specular_color = vec4(0, 0, 0, 0);

    if (diffuse_factor > 0.0f)
    {
        vec3 frag_to_eye = normalize(eye_position - v_frag_pos);
        vec3 reflected_vertex = normalize(reflect(direction, normalize(v_normal)));

        float specular_factor = dot(frag_to_eye, reflected_vertex);

        if (specular_factor > 0.0f)
        {
            /* Making shininess a power, the spread of the 
             * specular shading has greater contrast*/
            specular_factor = pow(specular_factor, material.shininess);
            specular_color = vec4(light.color * material.specular_intensity * specular_factor, 1.0f);
        }
    }

    return (ambient_color + diffuse_color + specular_color);
}

vec4 CalculateDirectionalLight()
{
    return CalculateLightByDirection(directional_light.base, directional_light.direction);
}

vec4 CalculateSinglePointLight(PointLight point_light)
{
    /* Direction the light is emmiting to hit this fragment point*/
    vec3 direction = v_frag_pos - point_light.position;

    float distance = length(direction);
    direction = normalize(direction);

    vec4 color = CalculateLightByDirection(point_light.base, direction);

    float attenuation = point_light.exponent * distance * distance + 
                        point_light.linear * distance +
                        point_light.constant;

    return color / attenuation;
}

vec4 CalculateSingleSpotLight(SpotLight spot_light)
{
    vec3 ray_direction = normalize(v_frag_pos - spot_light.base.position);
    float spot_light_factor = dot(ray_direction, spot_light.direction);

    if (spot_light_factor > spot_light.edge)
    {
        vec4 color = CalculateSinglePointLight(spot_light.base);

        return color * (1.0f - (1.0f - spot_light_factor) * (1.0f/(1.0f - spot_light.edge)));
    }
    else
    {
        return vec4(0, 0, 0, 0);
    }
}

vec4 CalculateMultiplePointLight()
{
    vec4 total_color = vec4(0, 0, 0, 0);

    for (int i = 0; i < point_light_count; i++)
    {
        total_color += CalculateSinglePointLight(point_lights[i]);
    }

    return total_color;
}

vec4 CalculateMultipleSpotLight()
{
    vec4 total_color = vec4(0, 0, 0, 0);

    for (int i = 0; i < spot_light_count; i++)
    {
        total_color += CalculateSingleSpotLight(spot_lights[i]);
    }

    return total_color;
}

void main()
{
    vec4 light_color = CalculateDirectionalLight();
    light_color += CalculateMultiplePointLight();
    light_color += CalculateMultipleSpotLight();

    color = texture(the_texture, v_tex_coord) * light_color;
}