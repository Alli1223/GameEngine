#include "stdafx.h"
#include "InfiniteWorld.h"


InfiniteWorld::InfiniteWorld()
{
}


InfiniteWorld::~InfiniteWorld()
{
}

std::shared_ptr<Cell> InfiniteWorld::GetCell(float X, float Y)
{
	std::shared_ptr<Cell> cell = Level.at({ X,Y });
	return cell;
}



void InfiniteWorld::OrientateCell(std::shared_ptr<Cell> node)
{
	// Check that the cells exist before querying
	if (GetCell(node->getX() - 1, node->getY()) != nullptr && GetCell(node->getX() + 1, node->getY()) != nullptr && GetCell(node->getX(), node->getY() - 1) != nullptr && GetCell(node->getX(), node->getY() + 1) != nullptr)
	{
		if (GetCell(node->getX() - 1, node->getY() - 1) != nullptr && GetCell(node->getX() + 1, node->getY() - 1) != nullptr && GetCell(node->getX() - 1, node->getY() - 1) != nullptr && GetCell(node->getX() - 1, node->getY() + 1) != nullptr && GetCell(node->getX() + 1, node->getY() + 1) != nullptr)
		{
			// Default to none before setting
			node->SetOrientation(Cell::Orientation::none);

			// Top Left //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType != node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType != node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								//if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									//if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::topLeft);
										}
									}
								}
							}
						}
					}
				}
			}

			// Top Middle //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType != node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							//if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								//if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::topMiddle);
										}
									}
								}
							}
						}
					}
				}
			}


			// Top Right //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType != node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType != node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							//if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										//if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::topRight);
										}
									}
								}
							}
						}
					}
				}
			}


			// Left //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType != node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							//if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									//if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::middleLeft);
										}
									}
								}
							}
						}
					}
				}
			}

			// Middle //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::middle);
										}
									}
								}
							}
						}
					}
				}
			}

			// Right //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType != node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								//if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										//if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::middleRight);
										}
									}
								}
							}
						}
					}
				}
			}

			// Bottom Left //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType != node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType != node->groundType)
						{ //TopLeft
							//if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										//if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::bottomLeft);
										}
									}
								}
							}
						}
					}
				}
			}

			// Bottom Middle //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType != node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									//if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										//if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::bottomMiddle);
										}
									}
								}
							}
						}
					}
				}
			}

			// Bottom Right //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType != node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType != node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								//if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									//if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::bottomRight);
										}
									}
								}
							}
						}
					}
				}
			}

			// Alone //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType != node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType != node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType != node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType != node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::alone);
										}
									}
								}
							}
						}
					}
				}
			}

			// Inverted Top Left //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::inv_topLeft);
										}
									}
								}
							}
						}
					}
				}
			}

			// Inverted Top Right //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::inv_topRight);
										}
									}
								}
							}
						}
					}
				}
			}

			// Inverted Bottom Left //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::inv_bottomLeft);
										}
									}
								}
							}
						}
					}
				}
			}

			// Inverted Bottom Right //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::inv_bottomRight);
										}
									}
								}
							}
						}
					}
				}
			}

			node->AssignType(1);
		}
	}
}