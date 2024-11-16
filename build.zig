const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "template",
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });
    exe.root_module.addIncludePath(b.path("include"));
    exe.root_module.addIncludePath(b.path("lib/log/src"));
    exe.root_module.addCSourceFiles(.{
        .root = b.path(""),
        .files = &[_][]const u8{
            "src/main.c",
            "lib/ds.c",
            "lib/log/src/log.c",
            "lib/macros.c",
        },
        .flags = &[_][]const u8{
            "-Wall",
            "-Wextra",
            "-Werror",
            "-pedantic",
            "-Wno-unused-parameter",
            "-Wshadow",
            "-std=c99",
        },
    });
    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);

    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
