﻿namespace Sharpmake.Exon
{
    using System.IO; // for Path.Combine
    using Sharpmake; // contains the entire Sharpmake object library.

    // Represents the project that will be generated by Sharpmake and that contains
    // the sample C++ code.
    [Generate]
    class Glfw : BaseProject
    {
        public static readonly string FolderName = "glfw-3.2.1";
        public Glfw()
        {
            // The name of the project in Visual Studio. The default is the name of
            // the class, but you usually want to override that.
            Name = "Extern.Glfw";

            // The directory that contains the source code we want to build is the
            // same as this one. This string essentially means "the directory of
            // the script you're reading right now."
            SourceRootPath = Path.Combine(Constants.ExternPath, FolderName);
            SourceFilesExcludeRegex.Add(
                @"\\tests\\",
                @"\\examples\\",
                @"\\deps\\",
                @"\\src\\wl_*",
                @"\\src\\x11_*",
                @"\\src\\glx_*",
                @"\\src\\mir_*",
                @"\\src\\linux_*",
                @"\\src\\posix_*",
                @"\\src\\cocoa_*"
            );
        }

        [Configure]
        public void ConfigureAll(Project.Configuration conf, Target target)
        {
            conf.IncludePaths.Add("include");
            conf.IncludePaths.Add(Path.Combine(Constants.ExternPath, "glad", "include"));
            conf.Output = Configuration.OutputType.Lib;
            conf.Defines.Add("_GLFW_WIN32");
        }
    }
}