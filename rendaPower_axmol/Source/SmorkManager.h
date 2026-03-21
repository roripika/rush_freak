//
//  SmorkManager.h
//  rendaPower
//
//  Created by ooharayukio on 2014/05/31.
//
//

#ifndef __rendaPower__SmorkManager__
#define __rendaPower__SmorkManager__

#include "axmol.h"

/**
 * 煙を起こす
 */
class SmorkManager : public ax::Node
{
public:
    CREATE_FUNC(SmorkManager);
    virtual bool init() override;
    
protected:
    
};

#endif /* defined(__rendaPower__SmorkManager__) */
