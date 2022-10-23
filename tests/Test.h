//
// Created by Anshul Saraf on 23/10/22.
//

#ifndef OPENGLBASICS_TEST_H
#define OPENGLBASICS_TEST_H

namespace Test {

#define TEST_RETURN bool
#define TEST_RETURN_SUCCESS 1
#define TEST_RETURN_FAILURE 0

    class Test{
    public:
        Test() {}
        virtual ~Test() {}

        virtual TEST_RETURN OnUpdate( float  deltaTime ) = 0;
        virtual TEST_RETURN OnRender() = 0;
        virtual TEST_RETURN OnImGuiRender() = 0;
    };
}

#endif //OPENGLBASICS_TEST_H
