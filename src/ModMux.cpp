/*
   Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011 Her Majesty
   the Queen in Right of Canada (Communications Research Center Canada)
 */
/*
   This file is part of ODR-DabMod.

   ODR-DabMod is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   ODR-DabMod is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with ODR-DabMod.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ModMux.h"

#include <assert.h>


#ifdef DEBUG
size_t ModMux::myCount = 0;
#endif


ModMux::ModMux(ModFormat inputFormat, ModFormat outputFormat) :
    ModPlugin((inputFormat), (outputFormat))
{
#ifdef DEBUG
    myOutputFile = NULL;
#endif
}


ModMux::~ModMux()
{
#ifdef DEBUG
    if (myOutputFile != NULL) {
        fclose(myOutputFile);
    }
#endif
}


int ModMux::process(std::vector<Buffer*> dataIn, std::vector<Buffer*> dataOut)
{
    assert(dataOut.size() == 1);

#ifdef DEBUG
    int ret = process(dataIn, dataOut[0]);
    if (myOutputFile == NULL) {
        char filename[128];
        sprintf(filename, "output.mux.%.2zu.%s", myCount, name());
        myOutputFile = fopen(filename, "w");
        ++myCount;
    }
    fwrite(dataOut[0]->getData(), dataOut[0]->getLength(), 1, myOutputFile);
    return ret;
#else
    return process(dataIn, dataOut[0]);
#endif
}
