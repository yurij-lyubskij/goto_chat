
#include "DBRepo.h"


//
//DBConnection Section
//

template<>
std::shared_ptr<iConnection> DBConnection<iConnection>::connection(){};					

//
//end of DBConnection Section
//