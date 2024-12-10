#include "Scene2.h"
Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	
	
}

Scene2::~Scene2() {}

bool Scene2::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;


	
	SDL_Surface* imgNPC = IMG_Load("Blinky.png");
	SDL_Texture* textureNPC = SDL_CreateTextureFromSurface(renderer, imgNPC);
	actor = new Actor(Vec3(),0.1f,0.0f,this, textureNPC);


	const int count = 375;

	sceneNodes.resize(count);
	//create some nodes
	for (int i = 0; i < count; ++i)
	{
		sceneNodes[i] = new Node(i);
	}

	// create Graph
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		return false;
	}
	//									4
	//									|
	//									|							
	//									|
	//           1----------------------2----------------------3
	//									|
	//									|
	//									|
	//									0


	// 2 To other nodes


	// DEGUB
	//int myNode = 1;
	//std::cout << "Neighbour of " << myNode << '\n';
	//for (Node* neighbour : graph->Neighbours(graph->getNodes(myNode)))
	//{
	//	std::cout << "Node: "<<neighbour->getLable() << '\n';
	//}

	////Path to find between two nodes 
	//std::vector<Node*> path = graph->FindPath(sceneNodes[0],sceneNodes[3]);

	//for (Node* value : path)
	//{
	//	std::cout << value->getLable() << '\n';
	//}
	//Create Tiles
	CreateTiles();
	int j = 336 / xAxis;
	int i = 336 % static_cast<int>(xAxis);
	tileArray[i][j]->SetRGBA(255, 255, 0, 255);
	return true;
}




void Scene2::CreateTiles()
{
	for (int i = 0; i < xAxis; ++i)
	{
		for (int j = 0; j < yAxis; ++j)
		{
			tileArray[i][j] = new Tile(Vec3(1.0f + i, 1.0f + j, 0.0f), 2.0f, 2.0f, this);
		}
	}
}


void Scene2::OnDestroy()
{
	for (int i = 0; i < xAxis; ++i)
	{
		for (int j = 0; j < yAxis; j++)
		{
			delete tileArray[i][j];
		}
	}
	delete actor;
}

void Scene2::Update(const float time)
{
	actor->Update();
	game->getPlayer()->Update(time);
}


void Scene2::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	for (int i = 0; i < xAxis; ++i)
	{
		for (int j=0;j<yAxis;j++)
		{
			tileArray[i][j]->Render();
		}
	}

	// render the player
	game->RenderPlayer(0.0f);
	actor->Render();
	SDL_RenderPresent(renderer);
}



void Scene2::HandleEvents(const SDL_Event& event)
{
	
		// Check if the mouse button was pressed
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			float gridWidth = 1000.0f / 25.0f;
			float gridHeight = 600.0f / 15.0f;
			Vec3 pos = Vec3(event.button.x, event.button.y, 0.0f);

			float screenWidth = 1000.0f;
			float screenHeight = 600.0f;

			// Number of tiles in the grid
			int numTilesX = 25;
			int numTilesY = 15;

			// Calculate tile size in screen space
			float tileWidth = screenWidth / numTilesX;
			float tileHeight = screenHeight / numTilesY;

			// Get mouse click position in screen space (from SDL event)
			float screenX = static_cast<float>(event.button.x); // Mouse X
			float screenY = static_cast<float>(event.button.y); // Mouse Y

			// Invert Y-axis for bottom-left corner to be (0,0) in grid coordinates
			// The screen origin is at the top-left, so we need to adjust the Y-axis:
			float adjustedY = screenHeight - screenY; // Invert Y-coordinate

			// Convert the screen coordinates to grid coordinates
			int gridX = static_cast<int>(screenX / tileWidth); // Get the grid X position
			int gridY = static_cast<int>(adjustedY / tileHeight); // Get the grid Y position
			
			// Check which mouse button was pressed
			if (event.button.button == SDL_BUTTON_LEFT) {
				tileArray[gridX][gridY]->SetRGBA(255, 0, 0, 255);
				tileArray[gridX][gridY]->valid = false;
				std::cout << "Left mouse button pressed at (" << gridX << ", " << gridY << ") Is Tile Valid: "  << tileArray[gridX][gridY]->valid <<  '\n';
				//std::cout << "Left mouse button pressed at (" << pos.x << ", " << pos.y << ")" << std::endl;
			}
			else if (event.button.button == SDL_BUTTON_RIGHT) {
				
					if(temp < worldPos.size())
					{
						actor->pos = worldPos[temp];
					
						temp++;
					}
					
					
				
			
				std::cout << "right mouse button pressed "<< worldPos.size() << '\n';
			}
			else if (event.button.button == SDL_BUTTON_MIDDLE) {

				std::cout << "Generating New Path"<< '\n';
				GenerateNewPath();
				std::vector<Node*> path = graph->DijkstraFindPath(sceneNodes[0], sceneNodes[336]);
				
				for (Node* node : path)
				{
					
				
					int j = node->getLable() / xAxis;
					int i =  node->getLable() % static_cast<int>(xAxis);
					worldPos.push_back(Vec3(i, j, 0.0f));
					tileArray[i][j]->SetRGBA(0, 0, 255, 255);
					std::cout << i << " , " <<j << "Node Label: "<< node->getLable()<< '\n';

				}
				
			}
			
		}
		// Exit on quit event
	
}
void PrintConnections(int from,int to)
{
	std::cout << "connection between " << from << " and " << to << "made\n";
}

void Scene2::GenerateNewPath()
{
	
	for (int i = 0; i < xAxis; ++i) {
		for (int j = 0; j < yAxis; ++j) {
			if (tileArray[i][j]->valid) {
				int currentNodeIndex = i + (25 * j);

				// Check and connect to the tile on the right
				if (InBould(i + 1, j) && tileArray[i + 1][j]->valid) {
					int rightNodeIndex = (i + 1) + (25 * j);
					graph->AddweightedConnection(graph->getNodes(currentNodeIndex), graph->getNodes(rightNodeIndex), 1.0f);
				}

				// Check and connect to the tile on the left
				if (InBould(i - 1, j) && tileArray[i - 1][j]->valid) {
					int leftNodeIndex = (i - 1) + (25 * j);
					graph->AddweightedConnection(graph->getNodes(currentNodeIndex), graph->getNodes(leftNodeIndex), 1.0f);
				}

				// Check and connect to the tile above
				if (InBould(i, j + 1) && tileArray[i][j + 1]->valid) {
					int aboveNodeIndex = i + (25 * (j + 1));
					graph->AddweightedConnection(graph->getNodes(currentNodeIndex), graph->getNodes(aboveNodeIndex), 1.0f);
				}

				// Check and connect to the tile below
				if (InBould(i, j - 1) && tileArray[i][j - 1]->valid) {
					int belowNodeIndex = i + (25 * (j - 1));
					graph->AddweightedConnection(graph->getNodes(currentNodeIndex), graph->getNodes(belowNodeIndex), 1.0f);
				}
			}
		}
	}
}


bool Scene2::InBould(const int i_, const int j_)
{
	
	return i_ >= 0 && i_ < xAxis && j_ >= 0 && j_ < yAxis;
}


//if (tileArray[j][i]->valid)
//{
//	if (InBould(j + 1, i) && tileArray[j + 1][i]->valid)
//	{
//		graph->AddweightedConnection(graph->getNodes(j + (14 * i)), graph->getNodes(j + 1 + (14 * i)), 1.0f);
//	}
//	//Below
//	if (InBould(j - 1, i) && tileArray[j - 1][i]->valid)
//	{
//		graph->AddweightedConnection(graph->getNodes(j + (14 * i)), graph->getNodes(j - 1 + (14 * i)), 1.0f);
//	}
//	//Right
//	if (InBould(j, i + 1) && tileArray[j][i + 1]->valid)
//	{
//		graph->AddweightedConnection(graph->getNodes(j + (14 * i)), graph->getNodes(j + (14 * i + 1)), 1.0f);
//	}
//	//Left
//	if (InBould(j, i - 1) && tileArray[j][i - 1]->valid)
//	{
//		graph->AddweightedConnection(graph->getNodes(j + (14 * i)), graph->getNodes(j + (14 * i - 1)), 1.0f);
//	}
//}


//// Check and connect to the tile below
				//if (InBould(i - 1, j) && tileArray[i - 1][j]->valid == true)
				//{
				//	graph->AddweightedConnection(graph->getNodes(i + (24* j)), graph->getNodes((i - 1) + (24 * j)), 1.0f);

				//	PrintConnections(i + (24 * j), (i - 1) + (24 * j));
				//}

				//// Check and connect to the tile to the right
				//if (InBould(i, j + 1) && tileArray[i][j + 1]->valid == true)
				//{
				//		graph->AddweightedConnection(graph->getNodes(i + (24 * j)), graph->getNodes(i + (24 * (j + 1))), 1.0f);
				//		PrintConnections(i + (24 * j), i  + (24 * (j + 1)));
				//}

				//// Check and connect to the tile to the left
				//if (InBould(i, j - 1) && tileArray[i][j - 1]->valid == true)
				//{
				//	graph->AddweightedConnection(graph->getNodes(i + (24 * j)), graph->getNodes(i + (24 * (j - 1))), 1.0f);
				//
				//	PrintConnections(i + (24 * j), i + (24 * (j - 1)));
				//}