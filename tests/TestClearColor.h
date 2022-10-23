//
// Created by Anshul Saraf on 23/10/22.
//

#ifndef OPENGLBASICS_TESTCLEARCOLOR_H
#define OPENGLBASICS_TESTCLEARCOLOR_H

#include "Test.h"

namespace Test {

    class TestClearColor : public Test {

    public:
        TestClearColor() ;
        ~TestClearColor() ;

        TEST_RETURN OnUpdate( float  deltaTime ) override;
        TEST_RETURN OnRender() override;
        TEST_RETURN OnImGuiRender() override;

    private:
        float m_ClearColor[4];
    };

}


#endif //OPENGLBASICS_TESTCLEARCOLOR_H
