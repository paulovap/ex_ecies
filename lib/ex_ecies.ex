defmodule ExEcies do
	@on_load :init

  def init() do
    path = :filename.join(:code.priv_dir(:ex_ecies), 'lib_elixir_ecies')
    :ok = :erlang.load_nif(path, 0)
    init_nif()
  end

  def generate_key() do
    {pub, priv} = :crypto.generate_key(:ecdh, :secp521r1)
    {Base.encode16(pub), Base.encode16(priv)}
  end

  def encrypt(data, pubKey) do
    encrypt_nif(data, pubKey)
  end

  def decrypt(data, privKey) do
    decrypt_nif(data, privKey)
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
