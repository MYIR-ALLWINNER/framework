void API_ENTRY(glActiveTexture)(GLenum texture) {
    CALL_GL_API(glActiveTexture, texture);
}
void API_ENTRY(glAttachShader)(GLuint program, GLuint shader) {
    CALL_GL_API(glAttachShader, program, shader);
}
void API_ENTRY(glBindAttribLocation)(GLuint program, GLuint index, const GLchar *name) {
    CALL_GL_API(glBindAttribLocation, program, index, name);
}
void API_ENTRY(glBindBuffer)(GLenum target, GLuint buffer) {
    CALL_GL_API(glBindBuffer, target, buffer);
}
void API_ENTRY(glBindFramebuffer)(GLenum target, GLuint framebuffer) {
    CALL_GL_API(glBindFramebuffer, target, framebuffer);
}
void API_ENTRY(glBindRenderbuffer)(GLenum target, GLuint renderbuffer) {
    CALL_GL_API(glBindRenderbuffer, target, renderbuffer);
}
void API_ENTRY(glBindTexture)(GLenum target, GLuint texture) {
    CALL_GL_API(glBindTexture, target, texture);
}
void API_ENTRY(glBlendColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    CALL_GL_API(glBlendColor, red, green, blue, alpha);
}
void API_ENTRY(glBlendEquation)(GLenum mode) {
    CALL_GL_API(glBlendEquation, mode);
}
void API_ENTRY(glBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha) {
    CALL_GL_API(glBlendEquationSeparate, modeRGB, modeAlpha);
}
void API_ENTRY(glBlendFunc)(GLenum sfactor, GLenum dfactor) {
    CALL_GL_API(glBlendFunc, sfactor, dfactor);
}
void API_ENTRY(glBlendFuncSeparate)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
    CALL_GL_API(glBlendFuncSeparate, sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}
void API_ENTRY(glBufferData)(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {
    CALL_GL_API(glBufferData, target, size, data, usage);
}
void API_ENTRY(glBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const void *data) {
    CALL_GL_API(glBufferSubData, target, offset, size, data);
}
GLenum API_ENTRY(glCheckFramebufferStatus)(GLenum target) {
    CALL_GL_API_RETURN(glCheckFramebufferStatus, target);
    return 0;
}
void API_ENTRY(glClear)(GLbitfield mask) {
    CALL_GL_API(glClear, mask);
}
void API_ENTRY(glClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    CALL_GL_API(glClearColor, red, green, blue, alpha);
}
void API_ENTRY(glClearDepthf)(GLfloat d) {
    CALL_GL_API(glClearDepthf, d);
}
void API_ENTRY(glClearStencil)(GLint s) {
    CALL_GL_API(glClearStencil, s);
}
void API_ENTRY(glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    CALL_GL_API(glColorMask, red, green, blue, alpha);
}
void API_ENTRY(glCompileShader)(GLuint shader) {
    CALL_GL_API(glCompileShader, shader);
}
void API_ENTRY(glCompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data) {
    CALL_GL_API(glCompressedTexImage2D, target, level, internalformat, width, height, border, imageSize, data);
}
void API_ENTRY(glCompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data) {
    CALL_GL_API(glCompressedTexSubImage2D, target, level, xoffset, yoffset, width, height, format, imageSize, data);
}
void API_ENTRY(glCopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
    CALL_GL_API(glCopyTexImage2D, target, level, internalformat, x, y, width, height, border);
}
void API_ENTRY(glCopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    CALL_GL_API(glCopyTexSubImage2D, target, level, xoffset, yoffset, x, y, width, height);
}
GLuint API_ENTRY(glCreateProgram)(void) {
    CALL_GL_API_RETURN(glCreateProgram);
    return 0;
}
GLuint API_ENTRY(glCreateShader)(GLenum type) {
    CALL_GL_API_RETURN(glCreateShader, type);
    return 0;
}
void API_ENTRY(glCullFace)(GLenum mode) {
    CALL_GL_API(glCullFace, mode);
}
void API_ENTRY(glDeleteBuffers)(GLsizei n, const GLuint *buffers) {
    CALL_GL_API(glDeleteBuffers, n, buffers);
}
void API_ENTRY(glDeleteFramebuffers)(GLsizei n, const GLuint *framebuffers) {
    CALL_GL_API(glDeleteFramebuffers, n, framebuffers);
}
void API_ENTRY(glDeleteProgram)(GLuint program) {
    CALL_GL_API(glDeleteProgram, program);
}
void API_ENTRY(glDeleteRenderbuffers)(GLsizei n, const GLuint *renderbuffers) {
    CALL_GL_API(glDeleteRenderbuffers, n, renderbuffers);
}
void API_ENTRY(glDeleteShader)(GLuint shader) {
    CALL_GL_API(glDeleteShader, shader);
}
void API_ENTRY(glDeleteTextures)(GLsizei n, const GLuint *textures) {
    CALL_GL_API(glDeleteTextures, n, textures);
}
void API_ENTRY(glDepthFunc)(GLenum func) {
    CALL_GL_API(glDepthFunc, func);
}
void API_ENTRY(glDepthMask)(GLboolean flag) {
    CALL_GL_API(glDepthMask, flag);
}
void API_ENTRY(glDepthRangef)(GLfloat n, GLfloat f) {
    CALL_GL_API(glDepthRangef, n, f);
}
void API_ENTRY(glDetachShader)(GLuint program, GLuint shader) {
    CALL_GL_API(glDetachShader, program, shader);
}
void API_ENTRY(glDisable)(GLenum cap) {
    CALL_GL_API(glDisable, cap);
}
void API_ENTRY(glDisableVertexAttribArray)(GLuint index) {
    CALL_GL_API(glDisableVertexAttribArray, index);
}
void API_ENTRY(glDrawArrays)(GLenum mode, GLint first, GLsizei count) {
    CALL_GL_API(glDrawArrays, mode, first, count);
}
void API_ENTRY(glDrawElements)(GLenum mode, GLsizei count, GLenum type, const void *indices) {
    CALL_GL_API(glDrawElements, mode, count, type, indices);
}
void API_ENTRY(glEnable)(GLenum cap) {
    CALL_GL_API(glEnable, cap);
}
void API_ENTRY(glEnableVertexAttribArray)(GLuint index) {
    CALL_GL_API(glEnableVertexAttribArray, index);
}
void API_ENTRY(glFinish)(void) {
    CALL_GL_API(glFinish);
}
void API_ENTRY(glFlush)(void) {
    CALL_GL_API(glFlush);
}
void API_ENTRY(glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
    CALL_GL_API(glFramebufferRenderbuffer, target, attachment, renderbuffertarget, renderbuffer);
}
void API_ENTRY(glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    CALL_GL_API(glFramebufferTexture2D, target, attachment, textarget, texture, level);
}
void API_ENTRY(glFrontFace)(GLenum mode) {
    CALL_GL_API(glFrontFace, mode);
}
void API_ENTRY(glGenBuffers)(GLsizei n, GLuint *buffers) {
    CALL_GL_API(glGenBuffers, n, buffers);
}
void API_ENTRY(glGenerateMipmap)(GLenum target) {
    CALL_GL_API(glGenerateMipmap, target);
}
void API_ENTRY(glGenFramebuffers)(GLsizei n, GLuint *framebuffers) {
    CALL_GL_API(glGenFramebuffers, n, framebuffers);
}
void API_ENTRY(glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers) {
    CALL_GL_API(glGenRenderbuffers, n, renderbuffers);
}
void API_ENTRY(glGenTextures)(GLsizei n, GLuint *textures) {
    CALL_GL_API(glGenTextures, n, textures);
}
void API_ENTRY(glGetActiveAttrib)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) {
    CALL_GL_API(glGetActiveAttrib, program, index, bufSize, length, size, type, name);
}
void API_ENTRY(glGetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) {
    CALL_GL_API(glGetActiveUniform, program, index, bufSize, length, size, type, name);
}
void API_ENTRY(glGetAttachedShaders)(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders) {
    CALL_GL_API(glGetAttachedShaders, program, maxCount, count, shaders);
}
GLint API_ENTRY(glGetAttribLocation)(GLuint program, const GLchar *name) {
    CALL_GL_API_RETURN(glGetAttribLocation, program, name);
    return -1;
}
void API_ENTRY(__glGetBooleanv)(GLenum pname, GLboolean *data) {
    CALL_GL_API(glGetBooleanv, pname, data);
}
void API_ENTRY(glGetBufferParameteriv)(GLenum target, GLenum pname, GLint *params) {
    CALL_GL_API(glGetBufferParameteriv, target, pname, params);
}
GLenum API_ENTRY(glGetError)(void) {
    CALL_GL_API_RETURN(glGetError);
    return 0;
}
void API_ENTRY(__glGetFloatv)(GLenum pname, GLfloat *data) {
    CALL_GL_API(glGetFloatv, pname, data);
}
void API_ENTRY(glGetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname, GLint *params) {
    CALL_GL_API(glGetFramebufferAttachmentParameteriv, target, attachment, pname, params);
}
void API_ENTRY(__glGetIntegerv)(GLenum pname, GLint *data) {
    CALL_GL_API(glGetIntegerv, pname, data);
}
void API_ENTRY(glGetProgramiv)(GLuint program, GLenum pname, GLint *params) {
    CALL_GL_API(glGetProgramiv, program, pname, params);
}
void API_ENTRY(glGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    CALL_GL_API(glGetProgramInfoLog, program, bufSize, length, infoLog);
}
void API_ENTRY(glGetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint *params) {
    CALL_GL_API(glGetRenderbufferParameteriv, target, pname, params);
}
void API_ENTRY(glGetShaderiv)(GLuint shader, GLenum pname, GLint *params) {
    CALL_GL_API(glGetShaderiv, shader, pname, params);
}
void API_ENTRY(glGetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    CALL_GL_API(glGetShaderInfoLog, shader, bufSize, length, infoLog);
}
void API_ENTRY(glGetShaderPrecisionFormat)(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision) {
    CALL_GL_API(glGetShaderPrecisionFormat, shadertype, precisiontype, range, precision);
}
void API_ENTRY(glGetShaderSource)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source) {
    CALL_GL_API(glGetShaderSource, shader, bufSize, length, source);
}
const GLubyte * API_ENTRY(__glGetString)(GLenum name) {
    CALL_GL_API_RETURN(glGetString, name);
    return NULL;
}
void API_ENTRY(glGetTexParameterfv)(GLenum target, GLenum pname, GLfloat *params) {
    CALL_GL_API(glGetTexParameterfv, target, pname, params);
}
void API_ENTRY(glGetTexParameteriv)(GLenum target, GLenum pname, GLint *params) {
    CALL_GL_API(glGetTexParameteriv, target, pname, params);
}
void API_ENTRY(glGetUniformfv)(GLuint program, GLint location, GLfloat *params) {
    CALL_GL_API(glGetUniformfv, program, location, params);
}
void API_ENTRY(glGetUniformiv)(GLuint program, GLint location, GLint *params) {
    CALL_GL_API(glGetUniformiv, program, location, params);
}
GLint API_ENTRY(glGetUniformLocation)(GLuint program, const GLchar *name) {
    CALL_GL_API_RETURN(glGetUniformLocation, program, name);
    return -1;
}
void API_ENTRY(glGetVertexAttribfv)(GLuint index, GLenum pname, GLfloat *params) {
    CALL_GL_API(glGetVertexAttribfv, index, pname, params);
}
void API_ENTRY(glGetVertexAttribiv)(GLuint index, GLenum pname, GLint *params) {
    CALL_GL_API(glGetVertexAttribiv, index, pname, params);
}
void API_ENTRY(glGetVertexAttribPointerv)(GLuint index, GLenum pname, void **pointer) {
    CALL_GL_API(glGetVertexAttribPointerv, index, pname, pointer);
}
void API_ENTRY(glHint)(GLenum target, GLenum mode) {
    CALL_GL_API(glHint, target, mode);
}
GLboolean API_ENTRY(glIsBuffer)(GLuint buffer) {
    CALL_GL_API_RETURN(glIsBuffer, buffer);
    return 0;
}
GLboolean API_ENTRY(glIsEnabled)(GLenum cap) {
    CALL_GL_API_RETURN(glIsEnabled, cap);
    return 0;
}
GLboolean API_ENTRY(glIsFramebuffer)(GLuint framebuffer) {
    CALL_GL_API_RETURN(glIsFramebuffer, framebuffer);
    return 0;
}
GLboolean API_ENTRY(glIsProgram)(GLuint program) {
    CALL_GL_API_RETURN(glIsProgram, program);
    return 0;
}
GLboolean API_ENTRY(glIsRenderbuffer)(GLuint renderbuffer) {
    CALL_GL_API_RETURN(glIsRenderbuffer, renderbuffer);
    return 0;
}
GLboolean API_ENTRY(glIsShader)(GLuint shader) {
    CALL_GL_API_RETURN(glIsShader, shader);
    return 0;
}
GLboolean API_ENTRY(glIsTexture)(GLuint texture) {
    CALL_GL_API_RETURN(glIsTexture, texture);
    return 0;
}
void API_ENTRY(glLineWidth)(GLfloat width) {
    CALL_GL_API(glLineWidth, width);
    
}
void API_ENTRY(glLinkProgram)(GLuint program) {
    CALL_GL_API(glLinkProgram, program);
}
void API_ENTRY(glPixelStorei)(GLenum pname, GLint param) {
    CALL_GL_API(glPixelStorei, pname, param);
}
void API_ENTRY(glPolygonOffset)(GLfloat factor, GLfloat units) {
    CALL_GL_API(glPolygonOffset, factor, units);
}
void API_ENTRY(glReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels) {
    CALL_GL_API(glReadPixels, x, y, width, height, format, type, pixels);
}
void API_ENTRY(glReleaseShaderCompiler)(void) {
    CALL_GL_API(glReleaseShaderCompiler);
}
void API_ENTRY(glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
    CALL_GL_API(glRenderbufferStorage, target, internalformat, width, height);
}
void API_ENTRY(glSampleCoverage)(GLfloat value, GLboolean invert) {
    CALL_GL_API(glSampleCoverage, value, invert);
}
void API_ENTRY(glScissor)(GLint x, GLint y, GLsizei width, GLsizei height) {
    CALL_GL_API(glScissor, x, y, width, height);
}
void API_ENTRY(glShaderBinary)(GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length) {
    CALL_GL_API(glShaderBinary, count, shaders, binaryformat, binary, length);
}
void API_ENTRY(glShaderSource)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length) {
    CALL_GL_API(glShaderSource, shader, count, string, length);
}
void API_ENTRY(glStencilFunc)(GLenum func, GLint ref, GLuint mask) {
    CALL_GL_API(glStencilFunc, func, ref, mask);
}
void API_ENTRY(glStencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask) {
    CALL_GL_API(glStencilFuncSeparate, face, func, ref, mask);
}
void API_ENTRY(glStencilMask)(GLuint mask) {
    CALL_GL_API(glStencilMask, mask);
}
void API_ENTRY(glStencilMaskSeparate)(GLenum face, GLuint mask) {
    CALL_GL_API(glStencilMaskSeparate, face, mask);
}
void API_ENTRY(glStencilOp)(GLenum fail, GLenum zfail, GLenum zpass) {
    CALL_GL_API(glStencilOp, fail, zfail, zpass);
}
void API_ENTRY(glStencilOpSeparate)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
    CALL_GL_API(glStencilOpSeparate, face, sfail, dpfail, dppass);
}
void API_ENTRY(glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels) {
    CALL_GL_API(glTexImage2D, target, level, internalformat, width, height, border, format, type, pixels);
}
void API_ENTRY(glTexParameterf)(GLenum target, GLenum pname, GLfloat param) {
    CALL_GL_API(glTexParameterf, target, pname, param);
}
void API_ENTRY(glTexParameterfv)(GLenum target, GLenum pname, const GLfloat *params) {
    CALL_GL_API(glTexParameterfv, target, pname, params);
}
void API_ENTRY(glTexParameteri)(GLenum target, GLenum pname, GLint param) {
    CALL_GL_API(glTexParameteri, target, pname, param);
}
void API_ENTRY(glTexParameteriv)(GLenum target, GLenum pname, const GLint *params) {
    CALL_GL_API(glTexParameteriv, target, pname, params);
}
void API_ENTRY(glTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels) {
    CALL_GL_API(glTexSubImage2D, target, level, xoffset, yoffset, width, height, format, type, pixels);
}
void API_ENTRY(glUniform1f)(GLint location, GLfloat v0) {
    CALL_GL_API(glUniform1f, location, v0);
}
void API_ENTRY(glUniform1fv)(GLint location, GLsizei count, const GLfloat *value) {
    CALL_GL_API(glUniform1fv, location, count, value);
}
void API_ENTRY(glUniform1i)(GLint location, GLint v0) {
    CALL_GL_API(glUniform1i, location, v0);
}
void API_ENTRY(glUniform1iv)(GLint location, GLsizei count, const GLint *value) {
    CALL_GL_API(glUniform1iv, location, count, value);
}
void API_ENTRY(glUniform2f)(GLint location, GLfloat v0, GLfloat v1) {
    CALL_GL_API(glUniform2f, location, v0, v1);
}
void API_ENTRY(glUniform2fv)(GLint location, GLsizei count, const GLfloat *value) {
    CALL_GL_API(glUniform2fv, location, count, value);
}
void API_ENTRY(glUniform2i)(GLint location, GLint v0, GLint v1) {
    CALL_GL_API(glUniform2i, location, v0, v1);
}
void API_ENTRY(glUniform2iv)(GLint location, GLsizei count, const GLint *value) {
    CALL_GL_API(glUniform2iv, location, count, value);
}
void API_ENTRY(glUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    CALL_GL_API(glUniform3f, location, v0, v1, v2);
}
void API_ENTRY(glUniform3fv)(GLint location, GLsizei count, const GLfloat *value) {
    CALL_GL_API(glUniform3fv, location, count, value);
}
void API_ENTRY(glUniform3i)(GLint location, GLint v0, GLint v1, GLint v2) {
    CALL_GL_API(glUniform3i, location, v0, v1, v2);
}
void API_ENTRY(glUniform3iv)(GLint location, GLsizei count, const GLint *value) {
    CALL_GL_API(glUniform3iv, location, count, value);
}
void API_ENTRY(glUniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    CALL_GL_API(glUniform4f, location, v0, v1, v2, v3);
}
void API_ENTRY(glUniform4fv)(GLint location, GLsizei count, const GLfloat *value) {
    CALL_GL_API(glUniform4fv, location, count, value);
}
void API_ENTRY(glUniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    CALL_GL_API(glUniform4i, location, v0, v1, v2, v3);
}
void API_ENTRY(glUniform4iv)(GLint location, GLsizei count, const GLint *value) {
    CALL_GL_API(glUniform4iv, location, count, value);
}
void API_ENTRY(glUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glUniformMatrix2fv, location, count, transpose, value);
}
void API_ENTRY(glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glUniformMatrix3fv, location, count, transpose, value);
}
void API_ENTRY(glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glUniformMatrix4fv, location, count, transpose, value);
}
void API_ENTRY(glUseProgram)(GLuint program) {
    CALL_GL_API(glUseProgram, program);
}
void API_ENTRY(glValidateProgram)(GLuint program) {
    CALL_GL_API(glValidateProgram, program);
}
void API_ENTRY(glVertexAttrib1f)(GLuint index, GLfloat x) {
    CALL_GL_API(glVertexAttrib1f, index, x);
}
void API_ENTRY(glVertexAttrib1fv)(GLuint index, const GLfloat *v) {
    CALL_GL_API(glVertexAttrib1fv, index, v);
}
void API_ENTRY(glVertexAttrib2f)(GLuint index, GLfloat x, GLfloat y) {
    CALL_GL_API(glVertexAttrib2f, index, x, y);
}
void API_ENTRY(glVertexAttrib2fv)(GLuint index, const GLfloat *v) {
    CALL_GL_API(glVertexAttrib2fv, index, v);
}
void API_ENTRY(glVertexAttrib3f)(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
    CALL_GL_API(glVertexAttrib3f, index, x, y, z);
}
void API_ENTRY(glVertexAttrib3fv)(GLuint index, const GLfloat *v) {
    CALL_GL_API(glVertexAttrib3fv, index, v);
}
void API_ENTRY(glVertexAttrib4f)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    CALL_GL_API(glVertexAttrib4f, index, x, y, z, w);
}
void API_ENTRY(glVertexAttrib4fv)(GLuint index, const GLfloat *v) {
    CALL_GL_API(glVertexAttrib4fv, index, v);
}
void API_ENTRY(glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
    CALL_GL_API(glVertexAttribPointer, index, size, type, normalized, stride, pointer);
}
void API_ENTRY(glViewport)(GLint x, GLint y, GLsizei width, GLsizei height) {
    CALL_GL_API(glViewport, x, y, width, height);
}
void API_ENTRY(glReadBuffer)(GLenum src) {
    CALL_GL_API(glReadBuffer, src);
}
void API_ENTRY(glDrawRangeElements)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices) {
    CALL_GL_API(glDrawRangeElements, mode, start, end, count, type, indices);
}
void API_ENTRY(glTexImage3D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels) {
    CALL_GL_API(glTexImage3D, target, level, internalformat, width, height, depth, border, format, type, pixels);
}
void API_ENTRY(glTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels) {
    CALL_GL_API(glTexSubImage3D, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}
void API_ENTRY(glCopyTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    CALL_GL_API(glCopyTexSubImage3D, target, level, xoffset, yoffset, zoffset, x, y, width, height);
}
void API_ENTRY(glCompressedTexImage3D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data) {
    CALL_GL_API(glCompressedTexImage3D, target, level, internalformat, width, height, depth, border, imageSize, data);
}
void API_ENTRY(glCompressedTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data) {
    CALL_GL_API(glCompressedTexSubImage3D, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}
void API_ENTRY(glGenQueries)(GLsizei n, GLuint *ids) {
    CALL_GL_API(glGenQueries, n, ids);
}
void API_ENTRY(glDeleteQueries)(GLsizei n, const GLuint *ids) {
    CALL_GL_API(glDeleteQueries, n, ids);
}
GLboolean API_ENTRY(glIsQuery)(GLuint id) {
    CALL_GL_API_RETURN(glIsQuery, id);
    return 0;
}
void API_ENTRY(glBeginQuery)(GLenum target, GLuint id) {
    CALL_GL_API(glBeginQuery, target, id);
}
void API_ENTRY(glEndQuery)(GLenum target) {
    CALL_GL_API(glEndQuery, target);
}
void API_ENTRY(glGetQueryiv)(GLenum target, GLenum pname, GLint *params) {
    CALL_GL_API(glGetQueryiv, target, pname, params);
}
void API_ENTRY(glGetQueryObjectuiv)(GLuint id, GLenum pname, GLuint *params) {
    CALL_GL_API(glGetQueryObjectuiv, id, pname, params);
}
GLboolean API_ENTRY(glUnmapBuffer)(GLenum target) {
    CALL_GL_API_RETURN(glUnmapBuffer, target);
    return 0;
}
void API_ENTRY(glGetBufferPointerv)(GLenum target, GLenum pname, void **params) {
    CALL_GL_API(glGetBufferPointerv, target, pname, params);
}
void API_ENTRY(glDrawBuffers)(GLsizei n, const GLenum *bufs) {
    CALL_GL_API(glDrawBuffers, n, bufs);
}
void API_ENTRY(glUniformMatrix2x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glUniformMatrix2x3fv, location, count, transpose, value);
}
void API_ENTRY(glUniformMatrix3x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glUniformMatrix3x2fv, location, count, transpose, value);
}
void API_ENTRY(glUniformMatrix2x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glUniformMatrix2x4fv, location, count, transpose, value);
}
void API_ENTRY(glUniformMatrix4x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glUniformMatrix4x2fv, location, count, transpose, value);
}
void API_ENTRY(glUniformMatrix3x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glUniformMatrix3x4fv, location, count, transpose, value);
}
void API_ENTRY(glUniformMatrix4x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glUniformMatrix4x3fv, location, count, transpose, value);
}
void API_ENTRY(glBlitFramebuffer)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {
    CALL_GL_API(glBlitFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}
void API_ENTRY(glRenderbufferStorageMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {
    CALL_GL_API(glRenderbufferStorageMultisample, target, samples, internalformat, width, height);
}
void API_ENTRY(glFramebufferTextureLayer)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) {
    CALL_GL_API(glFramebufferTextureLayer, target, attachment, texture, level, layer);
}
void * API_ENTRY(glMapBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) {
    CALL_GL_API_RETURN(glMapBufferRange, target, offset, length, access);
    return NULL;
}
void API_ENTRY(glFlushMappedBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length) {
    CALL_GL_API(glFlushMappedBufferRange, target, offset, length);
}
void API_ENTRY(glBindVertexArray)(GLuint array) {
    CALL_GL_API(glBindVertexArray, array);
}
void API_ENTRY(glDeleteVertexArrays)(GLsizei n, const GLuint *arrays) {
    CALL_GL_API(glDeleteVertexArrays, n, arrays);
}
void API_ENTRY(glGenVertexArrays)(GLsizei n, GLuint *arrays) {
    CALL_GL_API(glGenVertexArrays, n, arrays);
}
GLboolean API_ENTRY(glIsVertexArray)(GLuint array) {
    CALL_GL_API_RETURN(glIsVertexArray, array);
    return 0;
}
void API_ENTRY(glGetIntegeri_v)(GLenum target, GLuint index, GLint *data) {
    CALL_GL_API(glGetIntegeri_v, target, index, data);
}
void API_ENTRY(glBeginTransformFeedback)(GLenum primitiveMode) {
    CALL_GL_API(glBeginTransformFeedback, primitiveMode);
}
void API_ENTRY(glEndTransformFeedback)(void) {
    CALL_GL_API(glEndTransformFeedback);
}
void API_ENTRY(glBindBufferRange)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {
    CALL_GL_API(glBindBufferRange, target, index, buffer, offset, size);
}
void API_ENTRY(glBindBufferBase)(GLenum target, GLuint index, GLuint buffer) {
    CALL_GL_API(glBindBufferBase, target, index, buffer);
}
void API_ENTRY(glTransformFeedbackVaryings)(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode) {
    CALL_GL_API(glTransformFeedbackVaryings, program, count, varyings, bufferMode);
}
void API_ENTRY(glGetTransformFeedbackVarying)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name) {
    CALL_GL_API(glGetTransformFeedbackVarying, program, index, bufSize, length, size, type, name);
}
void API_ENTRY(glVertexAttribIPointer)(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer) {
    CALL_GL_API(glVertexAttribIPointer, index, size, type, stride, pointer);
}
void API_ENTRY(glGetVertexAttribIiv)(GLuint index, GLenum pname, GLint *params) {
    CALL_GL_API(glGetVertexAttribIiv, index, pname, params);
}
void API_ENTRY(glGetVertexAttribIuiv)(GLuint index, GLenum pname, GLuint *params) {
    CALL_GL_API(glGetVertexAttribIuiv, index, pname, params);
}
void API_ENTRY(glVertexAttribI4i)(GLuint index, GLint x, GLint y, GLint z, GLint w) {
    CALL_GL_API(glVertexAttribI4i, index, x, y, z, w);
}
void API_ENTRY(glVertexAttribI4ui)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) {
    CALL_GL_API(glVertexAttribI4ui, index, x, y, z, w);
}
void API_ENTRY(glVertexAttribI4iv)(GLuint index, const GLint *v) {
    CALL_GL_API(glVertexAttribI4iv, index, v);
}
void API_ENTRY(glVertexAttribI4uiv)(GLuint index, const GLuint *v) {
    CALL_GL_API(glVertexAttribI4uiv, index, v);
}
void API_ENTRY(glGetUniformuiv)(GLuint program, GLint location, GLuint *params) {
    CALL_GL_API(glGetUniformuiv, program, location, params);
}
GLint API_ENTRY(glGetFragDataLocation)(GLuint program, const GLchar *name) {
    CALL_GL_API_RETURN(glGetFragDataLocation, program, name);
    return 0;
}
void API_ENTRY(glUniform1ui)(GLint location, GLuint v0) {
    CALL_GL_API(glUniform1ui, location, v0);
}
void API_ENTRY(glUniform2ui)(GLint location, GLuint v0, GLuint v1) {
    CALL_GL_API(glUniform2ui, location, v0, v1);
}
void API_ENTRY(glUniform3ui)(GLint location, GLuint v0, GLuint v1, GLuint v2) {
    CALL_GL_API(glUniform3ui, location, v0, v1, v2);
}
void API_ENTRY(glUniform4ui)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    CALL_GL_API(glUniform4ui, location, v0, v1, v2, v3);
}
void API_ENTRY(glUniform1uiv)(GLint location, GLsizei count, const GLuint *value) {
    CALL_GL_API(glUniform1uiv, location, count, value);
}
void API_ENTRY(glUniform2uiv)(GLint location, GLsizei count, const GLuint *value) {
    CALL_GL_API(glUniform2uiv, location, count, value);
}
void API_ENTRY(glUniform3uiv)(GLint location, GLsizei count, const GLuint *value) {
    CALL_GL_API(glUniform3uiv, location, count, value);
}
void API_ENTRY(glUniform4uiv)(GLint location, GLsizei count, const GLuint *value) {
    CALL_GL_API(glUniform4uiv, location, count, value);
}
void API_ENTRY(glClearBufferiv)(GLenum buffer, GLint drawbuffer, const GLint *value) {
    CALL_GL_API(glClearBufferiv, buffer, drawbuffer, value);
}
void API_ENTRY(glClearBufferuiv)(GLenum buffer, GLint drawbuffer, const GLuint *value) {
    CALL_GL_API(glClearBufferuiv, buffer, drawbuffer, value);
}
void API_ENTRY(glClearBufferfv)(GLenum buffer, GLint drawbuffer, const GLfloat *value) {
    CALL_GL_API(glClearBufferfv, buffer, drawbuffer, value);
}
void API_ENTRY(glClearBufferfi)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {
    CALL_GL_API(glClearBufferfi, buffer, drawbuffer, depth, stencil);
}
const GLubyte * API_ENTRY(__glGetStringi)(GLenum name, GLuint index) {
    CALL_GL_API_RETURN(glGetStringi, name, index);
    return NULL;
}
void API_ENTRY(glCopyBufferSubData)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {
    CALL_GL_API(glCopyBufferSubData, readTarget, writeTarget, readOffset, writeOffset, size);
}
void API_ENTRY(glGetUniformIndices)(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices) {
    CALL_GL_API(glGetUniformIndices, program, uniformCount, uniformNames, uniformIndices);
}
void API_ENTRY(glGetActiveUniformsiv)(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params) {
    CALL_GL_API(glGetActiveUniformsiv, program, uniformCount, uniformIndices, pname, params);
}
GLuint API_ENTRY(glGetUniformBlockIndex)(GLuint program, const GLchar *uniformBlockName) {
    CALL_GL_API_RETURN(glGetUniformBlockIndex, program, uniformBlockName);
    return 0;
}
void API_ENTRY(glGetActiveUniformBlockiv)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params) {
    CALL_GL_API(glGetActiveUniformBlockiv, program, uniformBlockIndex, pname, params);
}
void API_ENTRY(glGetActiveUniformBlockName)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName) {
    CALL_GL_API(glGetActiveUniformBlockName, program, uniformBlockIndex, bufSize, length, uniformBlockName);
}
void API_ENTRY(glUniformBlockBinding)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) {
    CALL_GL_API(glUniformBlockBinding, program, uniformBlockIndex, uniformBlockBinding);
}
void API_ENTRY(glDrawArraysInstanced)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) {
    CALL_GL_API(glDrawArraysInstanced, mode, first, count, instancecount);
}
void API_ENTRY(glDrawElementsInstanced)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount) {
    CALL_GL_API(glDrawElementsInstanced, mode, count, type, indices, instancecount);
}
GLsync API_ENTRY(glFenceSync)(GLenum condition, GLbitfield flags) {
    CALL_GL_API_RETURN(glFenceSync, condition, flags);
    return NULL;
}
GLboolean API_ENTRY(glIsSync)(GLsync sync) {
    CALL_GL_API_RETURN(glIsSync, sync);
    return 0;
}
void API_ENTRY(glDeleteSync)(GLsync sync) {
    CALL_GL_API(glDeleteSync, sync);
}
GLenum API_ENTRY(glClientWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout) {
    CALL_GL_API_RETURN(glClientWaitSync, sync, flags, timeout);
    return 0;
}
void API_ENTRY(glWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout) {
    CALL_GL_API(glWaitSync, sync, flags, timeout);
}
void API_ENTRY(__glGetInteger64v)(GLenum pname, GLint64 *data) {
    CALL_GL_API(glGetInteger64v, pname, data);
}
void API_ENTRY(glGetSynciv)(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values) {
    CALL_GL_API(glGetSynciv, sync, pname, bufSize, length, values);
}
void API_ENTRY(glGetInteger64i_v)(GLenum target, GLuint index, GLint64 *data) {
    CALL_GL_API(glGetInteger64i_v, target, index, data);
}
void API_ENTRY(glGetBufferParameteri64v)(GLenum target, GLenum pname, GLint64 *params) {
    CALL_GL_API(glGetBufferParameteri64v, target, pname, params);
}
void API_ENTRY(glGenSamplers)(GLsizei count, GLuint *samplers) {
    CALL_GL_API(glGenSamplers, count, samplers);
}
void API_ENTRY(glDeleteSamplers)(GLsizei count, const GLuint *samplers) {
    CALL_GL_API(glDeleteSamplers, count, samplers);
}
GLboolean API_ENTRY(glIsSampler)(GLuint sampler) {
    CALL_GL_API_RETURN(glIsSampler, sampler);
    return 0;
}
void API_ENTRY(glBindSampler)(GLuint unit, GLuint sampler) {
    CALL_GL_API(glBindSampler, unit, sampler);
}
void API_ENTRY(glSamplerParameteri)(GLuint sampler, GLenum pname, GLint param) {
    CALL_GL_API(glSamplerParameteri, sampler, pname, param);
}
void API_ENTRY(glSamplerParameteriv)(GLuint sampler, GLenum pname, const GLint *param) {
    CALL_GL_API(glSamplerParameteriv, sampler, pname, param);
}
void API_ENTRY(glSamplerParameterf)(GLuint sampler, GLenum pname, GLfloat param) {
    CALL_GL_API(glSamplerParameterf, sampler, pname, param);
}
void API_ENTRY(glSamplerParameterfv)(GLuint sampler, GLenum pname, const GLfloat *param) {
    CALL_GL_API(glSamplerParameterfv, sampler, pname, param);
}
void API_ENTRY(glGetSamplerParameteriv)(GLuint sampler, GLenum pname, GLint *params) {
    CALL_GL_API(glGetSamplerParameteriv, sampler, pname, params);
}
void API_ENTRY(glGetSamplerParameterfv)(GLuint sampler, GLenum pname, GLfloat *params) {
    CALL_GL_API(glGetSamplerParameterfv, sampler, pname, params);
}
void API_ENTRY(glVertexAttribDivisor)(GLuint index, GLuint divisor) {
    CALL_GL_API(glVertexAttribDivisor, index, divisor);
}
void API_ENTRY(glBindTransformFeedback)(GLenum target, GLuint id) {
    CALL_GL_API(glBindTransformFeedback, target, id);
}
void API_ENTRY(glDeleteTransformFeedbacks)(GLsizei n, const GLuint *ids) {
    CALL_GL_API(glDeleteTransformFeedbacks, n, ids);
}
void API_ENTRY(glGenTransformFeedbacks)(GLsizei n, GLuint *ids) {
    CALL_GL_API(glGenTransformFeedbacks, n, ids);
}
GLboolean API_ENTRY(glIsTransformFeedback)(GLuint id) {
    CALL_GL_API_RETURN(glIsTransformFeedback, id);
    return 0;
}
void API_ENTRY(glPauseTransformFeedback)(void) {
    CALL_GL_API(glPauseTransformFeedback);
}
void API_ENTRY(glResumeTransformFeedback)(void) {
    CALL_GL_API(glResumeTransformFeedback);
}
void API_ENTRY(glGetProgramBinary)(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary) {
    CALL_GL_API(glGetProgramBinary, program, bufSize, length, binaryFormat, binary);
}
void API_ENTRY(glProgramBinary)(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length) {
    CALL_GL_API(glProgramBinary, program, binaryFormat, binary, length);
}
void API_ENTRY(glProgramParameteri)(GLuint program, GLenum pname, GLint value) {
    CALL_GL_API(glProgramParameteri, program, pname, value);
}
void API_ENTRY(glInvalidateFramebuffer)(GLenum target, GLsizei numAttachments, const GLenum *attachments) {
    CALL_GL_API(glInvalidateFramebuffer, target, numAttachments, attachments);
}
void API_ENTRY(glInvalidateSubFramebuffer)(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height) {
    CALL_GL_API(glInvalidateSubFramebuffer, target, numAttachments, attachments, x, y, width, height);
}
void API_ENTRY(glTexStorage2D)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) {
    CALL_GL_API(glTexStorage2D, target, levels, internalformat, width, height);
}
void API_ENTRY(glTexStorage3D)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) {
    CALL_GL_API(glTexStorage3D, target, levels, internalformat, width, height, depth);
}
void API_ENTRY(glGetInternalformativ)(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params) {
    CALL_GL_API(glGetInternalformativ, target, internalformat, pname, bufSize, params);
}
void API_ENTRY(glDispatchCompute)(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) {
    CALL_GL_API(glDispatchCompute, num_groups_x, num_groups_y, num_groups_z);
}
void API_ENTRY(glDispatchComputeIndirect)(GLintptr indirect) {
    CALL_GL_API(glDispatchComputeIndirect, indirect);
}
void API_ENTRY(glDrawArraysIndirect)(GLenum mode, const void *indirect) {
    CALL_GL_API(glDrawArraysIndirect, mode, indirect);
}
void API_ENTRY(glDrawElementsIndirect)(GLenum mode, GLenum type, const void *indirect) {
    CALL_GL_API(glDrawElementsIndirect, mode, type, indirect);
}
void API_ENTRY(glFramebufferParameteri)(GLenum target, GLenum pname, GLint param) {
    CALL_GL_API(glFramebufferParameteri, target, pname, param);
}
void API_ENTRY(glGetFramebufferParameteriv)(GLenum target, GLenum pname, GLint *params) {
    CALL_GL_API(glGetFramebufferParameteriv, target, pname, params);
}
void API_ENTRY(glGetProgramInterfaceiv)(GLuint program, GLenum programInterface, GLenum pname, GLint *params) {
    CALL_GL_API(glGetProgramInterfaceiv, program, programInterface, pname, params);
}
GLuint API_ENTRY(glGetProgramResourceIndex)(GLuint program, GLenum programInterface, const GLchar *name) {
    CALL_GL_API_RETURN(glGetProgramResourceIndex, program, programInterface, name);
    return 0;
}
void API_ENTRY(glGetProgramResourceName)(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name) {
    CALL_GL_API(glGetProgramResourceName, program, programInterface, index, bufSize, length, name);
}
void API_ENTRY(glGetProgramResourceiv)(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params) {
    CALL_GL_API(glGetProgramResourceiv, program, programInterface, index, propCount, props, bufSize, length, params);
}
GLint API_ENTRY(glGetProgramResourceLocation)(GLuint program, GLenum programInterface, const GLchar *name) {
    CALL_GL_API_RETURN(glGetProgramResourceLocation, program, programInterface, name);
    return 0;
}
void API_ENTRY(glUseProgramStages)(GLuint pipeline, GLbitfield stages, GLuint program) {
    CALL_GL_API(glUseProgramStages, pipeline, stages, program);
}
void API_ENTRY(glActiveShaderProgram)(GLuint pipeline, GLuint program) {
    CALL_GL_API(glActiveShaderProgram, pipeline, program);
}
GLuint API_ENTRY(glCreateShaderProgramv)(GLenum type, GLsizei count, const GLchar *const*strings) {
    CALL_GL_API_RETURN(glCreateShaderProgramv, type, count, strings);
    return 0;
}
void API_ENTRY(glBindProgramPipeline)(GLuint pipeline) {
    CALL_GL_API(glBindProgramPipeline, pipeline);
}
void API_ENTRY(glDeleteProgramPipelines)(GLsizei n, const GLuint *pipelines) {
    CALL_GL_API(glDeleteProgramPipelines, n, pipelines);
}
void API_ENTRY(glGenProgramPipelines)(GLsizei n, GLuint *pipelines) {
    CALL_GL_API(glGenProgramPipelines, n, pipelines);
}
GLboolean API_ENTRY(glIsProgramPipeline)(GLuint pipeline) {
    CALL_GL_API_RETURN(glIsProgramPipeline, pipeline);
    return 0;
}
void API_ENTRY(glGetProgramPipelineiv)(GLuint pipeline, GLenum pname, GLint *params) {
    CALL_GL_API(glGetProgramPipelineiv, pipeline, pname, params);
}
void API_ENTRY(glProgramUniform1i)(GLuint program, GLint location, GLint v0) {
    CALL_GL_API(glProgramUniform1i, program, location, v0);
}
void API_ENTRY(glProgramUniform2i)(GLuint program, GLint location, GLint v0, GLint v1) {
    CALL_GL_API(glProgramUniform2i, program, location, v0, v1);
}
void API_ENTRY(glProgramUniform3i)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2) {
    CALL_GL_API(glProgramUniform3i, program, location, v0, v1, v2);
}
void API_ENTRY(glProgramUniform4i)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    CALL_GL_API(glProgramUniform4i, program, location, v0, v1, v2, v3);
}
void API_ENTRY(glProgramUniform1ui)(GLuint program, GLint location, GLuint v0) {
    CALL_GL_API(glProgramUniform1ui, program, location, v0);
}
void API_ENTRY(glProgramUniform2ui)(GLuint program, GLint location, GLuint v0, GLuint v1) {
    CALL_GL_API(glProgramUniform2ui, program, location, v0, v1);
}
void API_ENTRY(glProgramUniform3ui)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) {
    CALL_GL_API(glProgramUniform3ui, program, location, v0, v1, v2);
}
void API_ENTRY(glProgramUniform4ui)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    CALL_GL_API(glProgramUniform4ui, program, location, v0, v1, v2, v3);
}
void API_ENTRY(glProgramUniform1f)(GLuint program, GLint location, GLfloat v0) {
    CALL_GL_API(glProgramUniform1f, program, location, v0);
}
void API_ENTRY(glProgramUniform2f)(GLuint program, GLint location, GLfloat v0, GLfloat v1) {
    CALL_GL_API(glProgramUniform2f, program, location, v0, v1);
}
void API_ENTRY(glProgramUniform3f)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    CALL_GL_API(glProgramUniform3f, program, location, v0, v1, v2);
}
void API_ENTRY(glProgramUniform4f)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    CALL_GL_API(glProgramUniform4f, program, location, v0, v1, v2, v3);
}
void API_ENTRY(glProgramUniform1iv)(GLuint program, GLint location, GLsizei count, const GLint *value) {
    CALL_GL_API(glProgramUniform1iv, program, location, count, value);
}
void API_ENTRY(glProgramUniform2iv)(GLuint program, GLint location, GLsizei count, const GLint *value) {
    CALL_GL_API(glProgramUniform2iv, program, location, count, value);
}
void API_ENTRY(glProgramUniform3iv)(GLuint program, GLint location, GLsizei count, const GLint *value) {
    CALL_GL_API(glProgramUniform3iv, program, location, count, value);
}
void API_ENTRY(glProgramUniform4iv)(GLuint program, GLint location, GLsizei count, const GLint *value) {
    CALL_GL_API(glProgramUniform4iv, program, location, count, value);
}
void API_ENTRY(glProgramUniform1uiv)(GLuint program, GLint location, GLsizei count, const GLuint *value) {
    CALL_GL_API(glProgramUniform1uiv, program, location, count, value);
}
void API_ENTRY(glProgramUniform2uiv)(GLuint program, GLint location, GLsizei count, const GLuint *value) {
    CALL_GL_API(glProgramUniform2uiv, program, location, count, value);
}
void API_ENTRY(glProgramUniform3uiv)(GLuint program, GLint location, GLsizei count, const GLuint *value) {
    CALL_GL_API(glProgramUniform3uiv, program, location, count, value);
}
void API_ENTRY(glProgramUniform4uiv)(GLuint program, GLint location, GLsizei count, const GLuint *value) {
    CALL_GL_API(glProgramUniform4uiv, program, location, count, value);
}
void API_ENTRY(glProgramUniform1fv)(GLuint program, GLint location, GLsizei count, const GLfloat *value) {
    CALL_GL_API(glProgramUniform1fv, program, location, count, value);
}
void API_ENTRY(glProgramUniform2fv)(GLuint program, GLint location, GLsizei count, const GLfloat *value) {
    CALL_GL_API(glProgramUniform2fv, program, location, count, value);
}
void API_ENTRY(glProgramUniform3fv)(GLuint program, GLint location, GLsizei count, const GLfloat *value) {
    CALL_GL_API(glProgramUniform3fv, program, location, count, value);
}
void API_ENTRY(glProgramUniform4fv)(GLuint program, GLint location, GLsizei count, const GLfloat *value) {
    CALL_GL_API(glProgramUniform4fv, program, location, count, value);
}
void API_ENTRY(glProgramUniformMatrix2fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glProgramUniformMatrix2fv, program, location, count, transpose, value);
}
void API_ENTRY(glProgramUniformMatrix3fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glProgramUniformMatrix3fv, program, location, count, transpose, value);
}
void API_ENTRY(glProgramUniformMatrix4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glProgramUniformMatrix4fv, program, location, count, transpose, value);
}
void API_ENTRY(glProgramUniformMatrix2x3fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glProgramUniformMatrix2x3fv, program, location, count, transpose, value);
}
void API_ENTRY(glProgramUniformMatrix3x2fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glProgramUniformMatrix3x2fv, program, location, count, transpose, value);
}
void API_ENTRY(glProgramUniformMatrix2x4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glProgramUniformMatrix2x4fv, program, location, count, transpose, value);
}
void API_ENTRY(glProgramUniformMatrix4x2fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glProgramUniformMatrix4x2fv, program, location, count, transpose, value);
}
void API_ENTRY(glProgramUniformMatrix3x4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glProgramUniformMatrix3x4fv, program, location, count, transpose, value);
}
void API_ENTRY(glProgramUniformMatrix4x3fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    CALL_GL_API(glProgramUniformMatrix4x3fv, program, location, count, transpose, value);
}
void API_ENTRY(glValidateProgramPipeline)(GLuint pipeline) {
    CALL_GL_API(glValidateProgramPipeline, pipeline);
}
void API_ENTRY(glGetProgramPipelineInfoLog)(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    CALL_GL_API(glGetProgramPipelineInfoLog, pipeline, bufSize, length, infoLog);
}
void API_ENTRY(glBindImageTexture)(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) {
    CALL_GL_API(glBindImageTexture, unit, texture, level, layered, layer, access, format);
}
void API_ENTRY(glGetBooleani_v)(GLenum target, GLuint index, GLboolean *data) {
    CALL_GL_API(glGetBooleani_v, target, index, data);
}
void API_ENTRY(glMemoryBarrier)(GLbitfield barriers) {
    CALL_GL_API(glMemoryBarrier, barriers);
}
void API_ENTRY(glMemoryBarrierByRegion)(GLbitfield barriers) {
    CALL_GL_API(glMemoryBarrierByRegion, barriers);
}
void API_ENTRY(glTexStorage2DMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) {
    CALL_GL_API(glTexStorage2DMultisample, target, samples, internalformat, width, height, fixedsamplelocations);
}
void API_ENTRY(glGetMultisamplefv)(GLenum pname, GLuint index, GLfloat *val) {
    CALL_GL_API(glGetMultisamplefv, pname, index, val);
}
void API_ENTRY(glSampleMaski)(GLuint maskNumber, GLbitfield mask) {
    CALL_GL_API(glSampleMaski, maskNumber, mask);
}
void API_ENTRY(glGetTexLevelParameteriv)(GLenum target, GLint level, GLenum pname, GLint *params) {
    CALL_GL_API(glGetTexLevelParameteriv, target, level, pname, params);
}
void API_ENTRY(glGetTexLevelParameterfv)(GLenum target, GLint level, GLenum pname, GLfloat *params) {
    CALL_GL_API(glGetTexLevelParameterfv, target, level, pname, params);
}
void API_ENTRY(glBindVertexBuffer)(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) {
    CALL_GL_API(glBindVertexBuffer, bindingindex, buffer, offset, stride);
}
void API_ENTRY(glVertexAttribFormat)(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) {
    CALL_GL_API(glVertexAttribFormat, attribindex, size, type, normalized, relativeoffset);
}
void API_ENTRY(glVertexAttribIFormat)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {
    CALL_GL_API(glVertexAttribIFormat, attribindex, size, type, relativeoffset);
}
void API_ENTRY(glVertexAttribBinding)(GLuint attribindex, GLuint bindingindex) {
    CALL_GL_API(glVertexAttribBinding, attribindex, bindingindex);
}
void API_ENTRY(glVertexBindingDivisor)(GLuint bindingindex, GLuint divisor) {
    CALL_GL_API(glVertexBindingDivisor, bindingindex, divisor);
}
void API_ENTRY(glBlendBarrier)(void) {
    CALL_GL_API(glBlendBarrier);
}
void API_ENTRY(glCopyImageSubData)(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) {
    CALL_GL_API(glCopyImageSubData, srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}
void API_ENTRY(glDebugMessageControl)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled) {
    CALL_GL_API(glDebugMessageControl, source, type, severity, count, ids, enabled);
}
void API_ENTRY(glDebugMessageInsert)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf) {
    CALL_GL_API(glDebugMessageInsert, source, type, id, severity, length, buf);
}

GLuint API_ENTRY(glGetDebugMessageLog)(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog) {
    CALL_GL_API_RETURN(glGetDebugMessageLog, count, bufSize, sources, types, ids, severities, lengths, messageLog);
    return 0;

}
void API_ENTRY(glPushDebugGroup)(GLenum source, GLuint id, GLsizei length, const GLchar *message) {
    CALL_GL_API(glPushDebugGroup, source, id, length, message);
}
void API_ENTRY(glPopDebugGroup)(void) {
    CALL_GL_API(glPopDebugGroup);
}
void API_ENTRY(glObjectLabel)(GLenum identifier, GLuint name, GLsizei length, const GLchar *label) {
    CALL_GL_API(glObjectLabel, identifier, name, length, label);
}
void API_ENTRY(glGetObjectLabel)(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label) {
    CALL_GL_API(glGetObjectLabel, identifier, name, bufSize, length, label);
}
void API_ENTRY(glObjectPtrLabel)(const void *ptr, GLsizei length, const GLchar *label) {
    CALL_GL_API(glObjectPtrLabel, ptr, length, label);
}
void API_ENTRY(glGetObjectPtrLabel)(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label) {
    CALL_GL_API(glGetObjectPtrLabel, ptr, bufSize, length, label);
}
void API_ENTRY(glGetPointerv)(GLenum pname, void **params) {
    CALL_GL_API(glGetPointerv, pname, params);
}
void API_ENTRY(glEnablei)(GLenum target, GLuint index) {
    CALL_GL_API(glEnablei, target, index);
}
void API_ENTRY(glDisablei)(GLenum target, GLuint index) {
    CALL_GL_API(glDisablei, target, index);
}
void API_ENTRY(glBlendEquationi)(GLuint buf, GLenum mode) {
    CALL_GL_API(glBlendEquationi, buf, mode);
}
void API_ENTRY(glBlendEquationSeparatei)(GLuint buf, GLenum modeRGB, GLenum modeAlpha) {
    CALL_GL_API(glBlendEquationSeparatei, buf, modeRGB, modeAlpha);
}
void API_ENTRY(glBlendFunci)(GLuint buf, GLenum src, GLenum dst) {
    CALL_GL_API(glBlendFunci, buf, src, dst);
}
void API_ENTRY(glBlendFuncSeparatei)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) {
    CALL_GL_API(glBlendFuncSeparatei, buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}
void API_ENTRY(glColorMaski)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) {
    CALL_GL_API(glColorMaski, index, r, g, b, a);
}
GLboolean API_ENTRY(glIsEnabledi)(GLenum target, GLuint index) {
    CALL_GL_API_RETURN(glIsEnabledi, target, index);
    return 0;
}
void API_ENTRY(glDrawElementsBaseVertex)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex) {
    CALL_GL_API(glDrawElementsBaseVertex, mode, count, type, indices, basevertex);
}
void API_ENTRY(glDrawRangeElementsBaseVertex)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex) {
    CALL_GL_API(glDrawRangeElementsBaseVertex, mode, start, end, count, type, indices, basevertex);
}
void API_ENTRY(glDrawElementsInstancedBaseVertex)(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex) {
    CALL_GL_API(glDrawElementsInstancedBaseVertex, mode, count, type, indices, instancecount, basevertex);
}
void API_ENTRY(glFramebufferTexture)(GLenum target, GLenum attachment, GLuint texture, GLint level) {
    CALL_GL_API(glFramebufferTexture, target, attachment, texture, level);
}
void API_ENTRY(glPrimitiveBoundingBox)(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW) {
    CALL_GL_API(glPrimitiveBoundingBox, minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
}
GLenum API_ENTRY(glGetGraphicsResetStatus)(void) {
    CALL_GL_API_RETURN(glGetGraphicsResetStatus);
    return 0;
}
void API_ENTRY(glReadnPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data) {
    CALL_GL_API(glReadnPixels, x, y, width, height, format, type, bufSize, data);
}
void API_ENTRY(glGetnUniformfv)(GLuint program, GLint location, GLsizei bufSize, GLfloat *params) {
    CALL_GL_API(glGetnUniformfv, program, location, bufSize, params);
}
void API_ENTRY(glGetnUniformiv)(GLuint program, GLint location, GLsizei bufSize, GLint *params) {
    CALL_GL_API(glGetnUniformiv, program, location, bufSize, params);
}
void API_ENTRY(glGetnUniformuiv)(GLuint program, GLint location, GLsizei bufSize, GLuint *params) {
    CALL_GL_API(glGetnUniformuiv, program, location, bufSize, params);
}
void API_ENTRY(glMinSampleShading)(GLfloat value) {
    CALL_GL_API(glMinSampleShading, value);
}
void API_ENTRY(glPatchParameteri)(GLenum pname, GLint value) {
    CALL_GL_API(glPatchParameteri, pname, value);
}
void API_ENTRY(glTexParameterIiv)(GLenum target, GLenum pname, const GLint *params) {
    CALL_GL_API(glTexParameterIiv, target, pname, params);
}
void API_ENTRY(glTexParameterIuiv)(GLenum target, GLenum pname, const GLuint *params) {
    CALL_GL_API(glTexParameterIuiv, target, pname, params);
}
void API_ENTRY(glGetTexParameterIiv)(GLenum target, GLenum pname, GLint *params) {
    CALL_GL_API(glGetTexParameterIiv, target, pname, params);
}
void API_ENTRY(glGetTexParameterIuiv)(GLenum target, GLenum pname, GLuint *params) {
    CALL_GL_API(glGetTexParameterIuiv, target, pname, params);
}
void API_ENTRY(glSamplerParameterIiv)(GLuint sampler, GLenum pname, const GLint *param) {
    CALL_GL_API(glSamplerParameterIiv, sampler, pname, param);
}
void API_ENTRY(glSamplerParameterIuiv)(GLuint sampler, GLenum pname, const GLuint *param) {
    CALL_GL_API(glSamplerParameterIuiv, sampler, pname, param);
}
void API_ENTRY(glGetSamplerParameterIiv)(GLuint sampler, GLenum pname, GLint *params) {
    CALL_GL_API(glGetSamplerParameterIiv, sampler, pname, params);
}
void API_ENTRY(glGetSamplerParameterIuiv)(GLuint sampler, GLenum pname, GLuint *params) {
    CALL_GL_API(glGetSamplerParameterIuiv, sampler, pname, params);
}
void API_ENTRY(glTexBuffer)(GLenum target, GLenum internalformat, GLuint buffer) {
    CALL_GL_API(glTexBuffer, target, internalformat, buffer);
}
void API_ENTRY(glTexBufferRange)(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) {
    CALL_GL_API(glTexBufferRange, target, internalformat, buffer, offset, size);
}
void API_ENTRY(glTexStorage3DMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) {
    CALL_GL_API(glTexStorage3DMultisample, target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

