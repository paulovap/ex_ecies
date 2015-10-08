defmodule ExEciesTest do
  use ExUnit.Case
  doctest ExEcies

  test "the truth" do
  	{pub, priv} = :crypto.generate_key(:ecdh, :secp521r1)
  	x = ExEcies.encrypt(Base.encode16(pub),"this is a laskdlaksdlaskdlaskldkfrecking test")
    IO.puts Base.encode16(x)
    "this is a frecking test" = ExEcies.decrypt(Base.encode16(priv), "asd")
  end
end
