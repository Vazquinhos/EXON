namespace Sharpmake.Exon
{
    using System.IO;

    public static class Constants
    {
        public static string SourcePath = "../../../source/";
        public static string ExternPath = "../../../extern/";
        public static string OutputPath = "../../../temp/output";
        public static string IntermediatePath = "../../../temp/intermediate/";
    }

    public abstract class BaseProject : Project
    {
        public BaseProject()
        {
            AddTargets(new Target(
                Platform.win64,
                DevEnv.vs2017,
                Optimization.Debug | Optimization.Release,
                OutputType.Dll | OutputType.Lib));
        }

        [Configure]
        public virtual void Configure(Configuration conf, Target target)
        {
            // Generate a different project depending on the .NET Framework,
            // because a configuration in Visual Studio cannot target a specific
            // version of the .NET Framework.
            conf.ProjectFileName = @"[project.Name].[target.DevEnv]";
            conf.ProjectPath = Path.Combine(Constants.OutputPath, "[target.DevEnv]");
            conf.IntermediatePath = Path.Combine(Constants.IntermediatePath, "[target.DevEnv]/obj/[target.Platform]/[target.Optimization]/[project.Name])");

            conf.Options.Add(Options.Vc.Compiler.Exceptions.EnableWithSEH);
            conf.Options.Add(Options.Vc.General.CharacterSet.MultiByte);
            conf.Options.Add(Options.Vc.Compiler.MinimalRebuild.Enable);
            conf.Options.Add(Options.Vc.General.WindowsTargetPlatformVersion.v10_0_17134_0);
            conf.Options.Add(target.Optimization == Optimization.Debug 
                ? Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDebugDLL : Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDLL);

            // Add the same library to its own include path
            conf.IncludePaths.Add(SourceRootPath);
            conf.IncludePaths.Add(Constants.ExternPath);
        }
    }

}
