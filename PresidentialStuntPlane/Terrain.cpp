#include "Terrain.h"

Mesh* terrain;

Terrain::Terrain() {
	char arrTerrain[] = "C://Users/crl_s/OneDrive/Escritorio/TerrainDifferent/terrain.obj";
	char* terrainFile = &arrTerrain[0];

	terrain = new Mesh(terrainFile);
}

void Terrain::Build()
{
	glPushMatrix();
	// Poner más o menos a la mitad de lo que se está escalando
	glTranslatef(0.0, 8.0, 0.0);
	terrain->NormalizeMesh();
	glScalef(20.0, 20.0, 20.0);
	terrain->Draw();
	terrain->DrawBoundingBox();
	glPopMatrix();
}

Terrain::~Terrain()
{
}
