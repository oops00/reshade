/**
 * Copyright (C) 2014 Patrick Mours. All rights reserved.
 * License: https://github.com/crosire/reshade#license
 */

#pragma once

#include "effect_parser.hpp"
#include <sstream>
#include <unordered_set>
#include <spirv_glsl.hpp>

namespace reshade::opengl
{
	#pragma region Forward Declarations
	struct opengl_pass_data;
	class opengl_runtime;
	#pragma endregion

	class opengl_effect_compiler
	{
	public:
		opengl_effect_compiler(opengl_runtime *runtime, const reshadefx::module &module, std::string &errors);

		bool run();

	private:
		void error(const std::string &message);
		void warning( const std::string &message);

		void visit_texture(const reshadefx::texture_info &texture_info);
		void visit_sampler(const reshadefx::sampler_info &sampler_info);
		void visit_uniform(const spirv_cross::CompilerGLSL &cross, const reshadefx::uniform_info &uniform_info);
		void visit_technique(const reshadefx::technique_info &technique_info);

		void compile_entry_point(spirv_cross::CompilerGLSL &cross, const std::vector<uint32_t> &spirv_bin, const spirv_cross::EntryPoint &entry);

		opengl_runtime *_runtime;
		const reshadefx::module *_module;
		bool _success;
		std::string &_errors;
		GLintptr _uniform_storage_offset = 0, _uniform_buffer_size = 0;
		std::vector<opengl_sampler_data> _sampler_bindings;
		std::unordered_map<std::string, GLuint> vs_entry_points;
		std::unordered_map<std::string, GLuint> fs_entry_points;
	};
}
