defmodule ExEciesTest do
  use ExUnit.Case
  doctest ExEcies

  test "the truth" do
  	pub = "0400e7e288c790970df59d7c0e74ab1770ceeeef5ca7802c8565c1a3a29fad43aff8b4d954b12f96093762484a45f7ca92c974acaab64db5c130a824fe948a810fa8d4007ce85575a118b9fb7dda70d950f096f6c682b4d34799e04e6a381bc0541554ba7e974f2c74c3e0e3ac1ce06cfb7f4f1f52a25bdf46bf498417867b93b37b5600e6"
  	priv = "f7c7edd024e3f9f288044929711c4a98503cbc1dfaf9c8a81b8149a0f0d11a273044dcd5d08599363e633caac2be0a07c95d7d510c2a761841706d7321a6d3bd54"
    :ok = ExEcies.encrypt(pub,"this is a frecking test")
  end
end
