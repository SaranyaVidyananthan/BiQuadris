#include "block.h"
#include "sblock.h"
#include "board.h"
#include "cell.h"
#include <iostream>

SBlock::SBlock( Board * g ): Block{'S', g }{}


SBlock::~SBlock() {
    shape.clear();
    shape.shrink_to_fit();
    temp.clear();
    temp.shrink_to_fit();
}


bool SBlock::set () {
    // check if the four cells needed for block are empty
    if( (g->getCell(0,3))->getStatus()  == true ) {
        temp.emplace_back( g->getCell(0,3));
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
        shape[index]->setType( 'S' );
        shape[index]->setStatus( false );
    }
    temp.clear();
    return true;
}


bool SBlock::move( int direction ){
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
            //for ( auto k:shape ) { shape[n].setStatus( false ); }
            for(int k = 0; i < 4; k++){
               shape[k]->setStatus(false);
            }
            temp.clear();
            return false;
        }
    
   }

    // set new shape to the temp cells
    for ( int index = 0; index < 4; index ++ ) {
        shape[index]->setStatus( true ); // set old shape cells to empty
        shape[index]->setType( ' ');
        shape[index] = temp[index];
        shape[index]->setType( 'S' );
        shape[index]->setStatus( false ); // set new cells to full
    }
    return true;
}


const char SBlock::getType(){
    return type;
}


// direction = 1, means clockwise, -1 means couterclockwise
bool SBlock::rotate( int direction ) {
    for (int n = 0; n < 4; n++) {
        shape[n]->setStatus( true );
    }
    if ( direction == 1 ) {  //clockwise
        if ( orientation + direction == 5 ) { direction = 1; }
        else { direction = orientation + direction; }
    }
    else { // counterclockwise
        if ( orientation + direction == 0 ) { direction = 4; }
        else { direction = orientation + direction; } 
    }
// now direction is the new orientation of the block
    return true;
}


void SBlock::print() {
    if ( g->getPlayer() == 2 ) { std::cout << "                             " << std::endl; }
    std::cout << " SS" << std::endl;
    if ( g->getPlayer() == 2 ) { std::cout << "                             " << std::endl; }
    std::cout << "SS"  << std::endl;
}
