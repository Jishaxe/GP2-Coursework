#include "Resources.h"



Resources::Resources()
{
}

IndexedModel* Resources::getModel(string name) {
	string filename = RESOURCES + name;

	// can we find this model in the map already?
	auto cached = models.find(filename);
	if (cached != models.end()) {
		cout << "Retrieved model " << filename << " from cache" << endl;
		return cached->second;
	}
	
	cout << "Loaded model " << filename << " and stored in cache" << endl;

	// if not, load it
	IndexedModel* model = new IndexedModel(OBJModel(filename).ToIndexedModel());
	models.insert(make_pair(filename, model));
	return model;
}

Resources::~Resources()
{
}
