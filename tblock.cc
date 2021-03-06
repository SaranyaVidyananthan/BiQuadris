#include "block.h"
#include "tblock.h"
#include "board.h"
#include "cell.h"
#include <iostream>

TBlock::TBlock(int level, Board * g ): Block{level,'T', g }{}


TBlock::~TBlock() {
    shape.clear();
    shape.shrink_to_fit();
    temp.clear();
    temp.shrink_to_fit();
}


bool TBlock::set () {
    // check if the four cells needed for block are empty
    if( (g->getCell(0,2))->getStatus()  == true ) {
        temp.emplace_back( g->getCell(0,2));
    }
    else { temp.clear(); return false; }
    if( (g->getCell(1,3))->getStatus()  == true ) {
        temp.emplace_back( g->getCell(1,3));
    }
    else { temp.clear(); return false; }
    if( (g->getCell(1,2))->getStatus() == true ) {
        temp.emplace_back( g->getCell(1,2) );
    }
    else { temp.clear(); return false; }
    if( (g->getCell(2,2))->getStatus() == true ) {
        temp.emplace_back( g->getCell(2,2));
    }
    else { temp.clear(); return false; }
    
    for (int index = 0; index < 4; index ++) {
        shape.emplace_back(temp[index]);
        shape[index]->setType( 'T' );
        shape[index]->setStatus( false );
        if ( g->getDisplay() ) { g->getDisplay()->fillRectangle( ( shape[index]->getX() + g->getX() )*scale, ( shape[index]->getY() + g->getY() )*scale, scale, scale, 6 ); }
    }
    temp.clear();
    return true;
}


bool TBlock::move( int direction ){
    for ( int n = 0; n < 4; n++ ) {
         shape[n]->setStatus( true );
         }

        // check if the shape cells can move, add cells to temp vector
    for ( int i = 0; i < 4; i ++ ) {
        // set the new x and y cells based on direction moving
        int a = 0;
        int b = 0;
        if ( direction == 2 ) { // right
            a = (shape[i]->getX()) + 1;
            b = (shape[i]->getY());
        }
        if ( direction == 3 ) { // down
            a = shape[i]->getX();
            b = (shape[i]->getY()) + 1;
        }
        if ( direction == 4 ) { // left
            a = (shape[i]->getX()) - 1;
            b = shape[i]->getY();
        }

        if ( a >= 0 && a < 11 && b >= 0 && b < 18 && g->getCell(a,b)->getStatus() == true ){ 
            temp.emplace_back( g->getCell(a,b) );
        }else {
            for(int k = 0; k < 4; k++){
               shape[k]->setStatus(false);
            }
            temp.clear();
            return false;
        }    
   }

    // set new shape to the temp cells
    for ( int index = 0; index < 4; index++ ) {
        shape[index]->setStatus( true ); // set old shape cells to empty
        shape[index]->setType(' '); // set old shape cella to no type
        if ( g->getDisplay() ) { g->getDisplay()->fillRectangle( ( shape[index]->getX() + g->getX() )*scale, ( shape[index]->getY() + g->getY() )*scale, scale, scale, 0 ); }
    }
    shape.clear();
    for ( int index = 0; index < 4; index++ ) {
        shape.emplace_back( temp[index] );
        shape.back()->setType( 'T' );
        shape.back()->setStatus( false ); // set new cells to full
        if ( g->getDisplay() ) { g->getDisplay()->fillRectangle( ( shape[index]->getX() + g->getX() )*scale, ( shape[index]->getY() + g->getY() )*scale, scale, scale, 6 ); }
    }

    temp.clear();
    return true;
}


const char TBlock::getType(){
    return type;
}


// direction = 1, means clockwise, -1 means couterclockwise
bool TBlock::rotate( int direction ) {
    for (int n = 0; n < 4; n++) { // set the old cells to empty
        shape[n]->setStatus( true );
    }
    // sets new orientation of block
    if ( direction == 1 ) {
        for ( int i = 0; i < 4; ++i ) {
            int a = shape[i]->getX();
            int b = shape[i]->getY();

            if ( orientation == 1 ) {
                if ( i == 3 ) {
                    a = shape[i]->getX() - 1;
                    b = shape[i]->getY() - 1;
                }
                if ( a >= 0 && a < 11 && b >= 0 && b < 18 && g->getCell(a,b)->getStatus() == true ){
                    temp.emplace_back( g->getCell( a, b ) );
                }
                else {
                    for( int k = 0; k < 4; ++k ){
                       shape[k]->setStatus(false);
                    }
                    temp.clear();
                    return false;
                }
            }

            else if ( orientation == 2 ) {
        	if ( i == 3 ) { 
		     a = shape[i]->getX() + 1;
		     b = shape[i]->getY() + 2; 
		}
                else if ( i == 0 ) { b = shape[i]->getY() + 1; }	   
                if ( a >= 0 && a < 11 && b >= 0 && b < 18 && g->getCell(a,b)->getStatus() == true ){
                    temp.emplace_back( g->getCell( a, b ) );
                }
                else {
                    for( int k = 0; k < 4; ++k ){
                       shape[k]->setStatus(false);
                    }
                    temp.clear();
                    return false;
                }
            }

            else if ( orientation == 3 ) {
                if ( i == 1 ) { 
		    a = shape[i]->getX() - 1;
                    b = shape[i]->getY() - 1;
		}
                else if ( i == 3 ) { 
		    a = shape[i]->getX() - 2; 
		    b = shape[i]->getY() - 2; 
		}
                if ( a >= 0 && a < 11 && b >= 0 && b < 18 && g->getCell(a,b)->getStatus() == true ){
                   temp.emplace_back( g->getCell( a, b ) );
                }
                else {
                   for( int k = 0; k < 4; ++k ){
                       shape[k]->setStatus(false);
                    }
                    temp.clear();
                    return false;
                }
            }
            else if ( orientation == 4 ) {
                if ( i == 0 ) { b = shape[i]->getY() - 1; }
                else if ( i == 1 ) {
                   a = shape[i]->getX() + 1;
                   b = shape[i]->getY() + 1;
                }
		else if ( i == 3 ) {
	           a = shape[i]->getX() + 2;
            	   b = shape[i]->getY() + 1;
		}
                if ( a >= 0 && a < 11 && b >= 0 && b < 18 && g->getCell(a,b)->getStatus() == true ){
                   temp.emplace_back( g->getCell( a, b ) );
                }
                else {
                    for( int k = 0; k < 4; ++k ){
                       shape[k]->setStatus(false);
                    }
                    temp.clear();
                    return false;
                }
            }
        }
    }

    else if ( direction == -1 ) { // counterclockwise
        for ( int i = 0; i < 4; ++i ) {
            int a = shape[i]->getX();
            int b = shape[i]->getY();
        
            if ( orientation == 1 ) {
                if ( i == 0 ) { b = shape[i]->getY() + 1; }
		else if ( i == 1 ) {
                    a = shape[i]->getX() - 1;
                    b = shape[i]->getY() - 1;
                }
                else if ( i == 3 ) {
                    a = shape[i]->getX() - 2;
                    b = shape[i]->getY() - 1;
                }

                if ( a >= 0 && a < 11 && b >= 0 && b < 18 && g->getCell(a,b)->getStatus() == true ){
                    temp.emplace_back( g->getCell( a, b ) );
                }
                else {
                    for( int k = 0; k < 4; ++k ){
                       shape[k]->setStatus(false);
                    }
                    temp.clear();
                    return false;
                }
            }

            else if ( orientation == 2 ) {
                if ( i == 3 ) {
                    a = shape[i]->getX() + 1;
                    b = shape[i]->getY() + 1;
                }
                if ( a >= 0 && a < 11 && b >= 0 && b < 18 && g->getCell(a,b)->getStatus() == true ){
                    temp.emplace_back( g->getCell( a, b ) );
                }
                else {
                    for( int k = 0; k < 4; ++k ){
                       shape[k]->setStatus(false);
                    }
                    temp.clear();
                    return false;
                }
            }
            else if ( orientation == 3 ) {
                if ( i == 0 ) { b = shape[i]->getY() - 1; }
                else if ( i == 3 ) {       
                   a = shape[i]->getX() - 1;
                   b = shape[i]->getY() - 2;
                }
                if ( a >= 0 && a < 11 && b >= 0 && b < 18 && g->getCell(a,b)->getStatus() == true ){
                   temp.emplace_back( g->getCell( a, b ) );
                }
                else {
                    for( int k = 0; k < 4; ++k ){
                       shape[k]->setStatus(false);
                    }
                    temp.clear();
                    return false;
                }
            }
            else if ( orientation == 4 ) {
                if ( i == 1 ) { 
		    a = shape[i]->getX() + 1; 
		    b = shape[i]->getY() + 1; 
	        }
                else if ( i == 3 ) {
                   a = shape[i]->getX() + 2;
                   b = shape[i]->getY() + 2;
                }
                if ( a >= 0 && a < 11 && b >= 0 && b < 18 && g->getCell(a,b)->getStatus() == true ){
                   temp.emplace_back( g->getCell( a, b ) );
                }
                else {
                    for( int k = 0; k < 4; ++k ){
                       shape[k]->setStatus(false);
                    }
                    temp.clear();
                    return false;
                }
            }
        }
    }
    // set new shape to the temp cells
    for ( int index = 0; index < 4; index++ ) {
        shape[index]->setStatus( true ); // set old shape cells to empty
        shape[index]->setType(' '); // set old shape cells to no type
        if ( g->getDisplay() ) { g->getDisplay()->fillRectangle( ( shape[index]->getX() + g->getX() )*scale , ( shape[index]->getY() + g->getY() )*scale , scale, scale, 0 ); }
    }
    shape.clear();
    for ( int index = 0; index < 4; index++ ) {
        shape.emplace_back( temp[index] );
        shape.back()->setType( 'T' );
        shape.back()->setStatus( false ); // set new cells to full
        if ( g->getDisplay() ) { g->getDisplay()->fillRectangle( ( shape[index]->getX() + g->getX() )*scale, ( shape[index]->getY() + g->getY() )*scale, scale, scale, 6 ); }
    }
    temp.clear();
    if ( direction == 1 ) {  //clockwise
        if ( orientation + direction == 5 ) { orientation = 1; }
        else { orientation = orientation + direction; }
    }
    else { // counterclockwise
        if ( orientation + direction == 0 ) { orientation = 4; }
        else { orientation = orientation + direction; }
    }
    // now direction is the new orientation of the block
    return true;
}


void TBlock::print() {
    if ( g->getPlayer() == 2 ) { std::cout << "                  "; }
    std::cout << "TTT" << std::endl;
    if ( g->getDisplay() ) { g->getDisplay()->fillRectangle( ( 0 + g->getX() )*scale, ( 21 + g->getY() )*scale, scale*3, scale, 6 ); }
    if ( g->getPlayer() == 2 ) { std::cout << "                  "; }
    std::cout << " T " << std::endl;
    if ( g->getDisplay() ) { g->getDisplay()->fillRectangle( ( 1 + g->getX() )*scale, ( 22 + g->getY() )*scale, scale, scale, 6 ); }
}


