#include "Terrain.h"

Mesh* terrain;

Terrain::Terrain() {
	//char arrTerrain[] = "C://Users/crl_s/OneDrive/Escritorio/TerrainDifferent/terrain.obj"; //SOTO

	//char arrTerrain[] = "C://Users/ednamo/Desktop/TerrainDifferent/terrain.obj"; //NAVA

	char arrTerrain[] = "C://Users/diego/source/repos/objects/TerrainDifferent/terrain.obj"; //DEUS

	char* terrainFile = &arrTerrain[0];

	terrain = new Mesh(terrainFile);
}

void Terrain::Build()
{
	glPushMatrix();
	// Poner más o menos a la mitad de lo que se está escalando
	glTranslatef(0.0, 15.0, 0.0);
	terrain->NormalizeMesh();
	glScalef(40.0, 40.0, 40.0);
	terrain->Draw();
	//terrain->DrawBoundingBox();
	glPopMatrix();
}

Terrain::~Terrain()
{
}
