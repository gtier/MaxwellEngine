//
//  MaxwellUtils.h
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/15/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#ifndef MaxwellUtils_h
#define MaxwellUtils_h

#include <memory>
#include <vector>

namespace mes {
    typedef std::unique_ptr<std::vector<float>> VectorFloat_uptr;
    typedef std::unique_ptr<std::vector<int>> VectorInt_uptr;
    typedef std::unique_ptr<std::vector<double>> VectorDouble_uptr;
}

#endif /* MaxwellUtils_h */
