﻿namespace Sharpmake.Exon
{
    using System.IO; // for Path.Combine
    using Sharpmake; // contains the entire Sharpmake object library.

    // Represents the project that will be generated by Sharpmake and that contains
    // the sample C++ code.
    [Generate]
    class Glad : BaseProject
    {
        public static readonly string FolderName = "glad";
        public Glad()
        {
            // The name of the project in Visual Studio. The default is the name of
            // the class, but you usually want to override that.
            Name = "Extern.Glad";

            // The directory that contains the source code we want to build is the
            // same as this one. This string essentially means "the directory of
            // the script you're reading right now."
            SourceRootPath = Path.Combine(Constants.ExternPath, FolderName);
        }

        [Configure]
        public void ConfigureAll(Project.Configuration conf, Target target)
        {
            conf.IncludePaths.Add(Path.Combine("include"));
            conf.Output = Configuration.OutputType.Lib;
        }
    }
}