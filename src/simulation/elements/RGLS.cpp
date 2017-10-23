#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_RGLS PT_RGLS 186
Element_RGLS::Element_RGLS()
{
	Identifier = "DEFAULT_PT_RGLS";
	Name = "RGLS";
	Colour = PIXPACK(0x665A50);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 100;

	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 150;
	Description = "Reinforced Glass. Breaks under 125 pressure and reflects 25% of photons.";

	Properties = TYPE_SOLID | PROP_NEUTPASS | PROP_HOT_GLOW | PROP_SPARKSETTLE;

	LowPressure = IPL;
	LowPressureTransition = PT_BGLA;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 2423.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_RGLS::update;
}

//#TPT-Directive ElementHeader Element_RGLS static int update(UPDATE_FUNC_ARGS)
int Element_RGLS::update(UPDATE_FUNC_ARGS)
{
	parts[i].pavg[0] = parts[i].pavg[1];
	parts[i].pavg[1] = sim->pv[y/CELL][x/CELL];
	float diff = parts[i].pavg[1] - parts[i].pavg[0];
	if (diff > 0.25f || diff < -0.25f)
	{
		sim->part_change_type(i,x,y,PT_BGLA);
	}
	return 0;
}


Element_RGLS::~Element_RGLS() {}
