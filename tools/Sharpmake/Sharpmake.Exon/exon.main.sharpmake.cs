[module: Sharpmake.Include("exon.common.sharpmake.cs")]
[module: Sharpmake.Include("extern.glfw.sharpmake.cs")]
[module: Sharpmake.Include("extern.glad.sharpmake.cs")]
[module: Sharpmake.Include("extern.glm.sharpmake.cs")]

namespace Sharpmake.Exon
{
    using System.IO;

    [Generate]
    class ExonApp : BaseProject
    {
        public static readonly string GlfwFolderName = "source";
        public ExonApp()
        {
            // The name of the project in Visual Studio. The default is the name of
            // the class, but you usually want to override that.
            Name = "Exon.App";

            // The directory that contains the source code we want to build is the
            // same as this one. This string essentially means "the directory of
            // the script you're reading right now."
            SourceRootPath = Path.Combine(Constants.SourcePath);
        }

        [Configure]
        public void ConfigureAll(Project.Configuration conf, Target target)
        {
            conf.IncludePaths.Add(Path.Combine("../extern/", Glfw.FolderName, "include"));
            conf.IncludePaths.Add(Path.Combine("../extern/", Glad.FolderName, "include"));
            conf.IncludePaths.Add(Path.Combine("../extern/", Glm.FolderName));
            conf.Output = Configuration.OutputType.Exe;
            conf.AddPrivateDependency<Glfw>(target);
            conf.AddPrivateDependency<Glad>(target);
            conf.DependenciesLibraryFiles.Add("opengl32.lib");
        }
    }

    // Represents the solution that will be generated and that will contain the
    // project with the sample code.
    [Generate]
    class Exon : Solution
    {
        public Exon()
        {
            // The name of the solution.
            Name = "Exon";

            AddTargets(new Target(
                Platform.win64,
                DevEnv.vs2017,
                Optimization.Debug | Optimization.Release,
                OutputType.Dll | OutputType.Lib));
        }

        // Configure for all 4 generated targets. Note that the type of the
        // configuration object is of type Solution.Configuration this time.
        // (Instead of Project.Configuration.)
        [Configure]
        public void ConfigureAll(Solution.Configuration conf, Target target)
        {
            // Puts the generated solution in the /generated folder too.
            conf.SolutionPath = Path.Combine(Constants.OutputPath, "[target.DevEnv]");

            // Adds the project described by BasicsProject into the solution.
            // Note that this is done in the configuration, so you can generate
            // solutions that contain different projects based on their target.
            //
            // You could, for example, exclude a project that only supports 64-bit
            // from the 32-bit targets.
            conf.AddProject<Glfw>(target);
            conf.AddProject<Glad>(target);
            conf.AddProject<Glm>(target);
            conf.AddProject<ExonApp>(target);
        }

        [Main]
        public static void SharpmakeMain(Arguments sharpmakeArgs)
        {
            // Tells Sharpmake to generate the solution described by
            // BasicsSolution.
            sharpmakeArgs.Generate<Exon>();
        }
    }
}
