defmodule ExEcies.Mixfile do
  use Mix.Project

  def project do
    [app: :ex_ecies,
     version: "0.0.2",
     elixir: "~> 1.0",
     compilers: [:make, :elixir, :app],
     build_embedded: Mix.env == :prod,
     start_permanent: Mix.env == :prod,
     aliases: aliases,
     deps: deps]
  end

  defp aliases do
    # Execute the usual mix clean and our Makefile clean task
    [clean: ["clean", "clean.make"]]
  end
  # Configuration for the OTP application
  #
  # Type "mix help compile.app" for more information
  def application do
    [applications: [:logger]]
  end

  # Dependencies can be Hex packages:
  #
  #   {:mydep, "~> 0.3.0"}
  #
  # Or git/path repositories:
  #
  #   {:mydep, git: "https://github.com/elixir-lang/mydep.git", tag: "0.1.0"}
  #
  # Type "mix help deps" for more examples and options
  defp deps do
    []
  end
end

###################
# Make file Tasks #
###################

defmodule Mix.Tasks.Compile.Make do
  @shortdoc "Compiles helper in c_src"

  def run(_) do
    {result, _error_code} = System.cmd("make", [], stderr_to_stdout: true)
    Mix.shell.info result

    :ok
  end
end

defmodule Mix.Tasks.Clean.Make do
  @shortdoc "Cleans helper in c_src"

  def run(_) do
    {result, _error_code} = System.cmd("make", ['clean'], stderr_to_stdout: true)
    Mix.shell.info result

    :ok
  end
end
