#pragma once
#include <vector>
#include <glad/glad.h>

namespace exon
{
    namespace ogl
    {
        void CheckErrors()
        {
#define CASE_GL_ERROR(caseenum, Description) case caseenum: OutputDebugString(#caseenum); OutputDebugString(Description); break
            GLenum lastError = glGetError();
            if (lastError != GL_NO_ERROR)
            {
                switch (lastError)
                {
                    //                    CASE_GL_ERROR(GL_NO_ERROR, "No error has been recorded.The value of this symbolic constant is guaranteed to be 0.");
                    CASE_GL_ERROR(GL_INVALID_ENUM, "An unacceptable value is specified for an enumerated argument.The offending command is ignored and has no other side effect than to set the error flag");
                    CASE_GL_ERROR(GL_INVALID_VALUE, " numeric argument is out of range.The offending command is ignored and has no other side effect than to set the error flag.");
                    CASE_GL_ERROR(GL_INVALID_OPERATION, "The specified operation is not allowed in the current state.The offending command is ignored and has no other side effect than to set the error flag.");
                    CASE_GL_ERROR(GL_STACK_OVERFLOW, "This command would cause a stack overflow.The offending command is ignored and has no other side effect than to set the error flag.");
                    CASE_GL_ERROR(GL_STACK_UNDERFLOW, "This command would cause a stack underflow.The offending command is ignored and has no other side effect than to set the error flag.");
                    CASE_GL_ERROR(GL_OUT_OF_MEMORY, "There is not enough memory left to execute the command.The state of the GL is undefined, except for the state of the error flags, after this error is recorded.");
                    //CASE_GL_ERROR(GL_TABLE_TOO_LARGE, "The specified table exceeds the implementation's maximum supported table size. The offending command is ignored and has no other side effect than to set the error flag.");
                }
            }
#undef CASE_GL_ERROR
        }
    }
}