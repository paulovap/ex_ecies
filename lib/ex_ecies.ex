defmodule ExEcies do
	@on_load :init

  def init() do
    :ok = :erlang.load_nif("./priv/lib_elixir_ecies", 0)
    init_nif()
  end

  def encrypt(pubKey, data) do
    encrypt_nif(pubKey, data)
  end

  def decrypt(privKey, data) do
    decrypt_nif(privKey, data)
  end

  defp init_nif() do
  	"NIF library not loaded"
  end

  defp encrypt_nif(_, _) do
    "NIF library not loaded"
  end

  defp decrypt_nif(_, _) do
    "NIF library not loaded"
  end
end
