@static if VERSION < v"1.0.0-"
    pushfirst! = unshift!
end
pushfirst!(LOAD_PATH, "../build/types")

using ZCM
using juliazcmtypes: example_t,
                     encoded_t

# declare a new msg and populate it
msg = example_t()
msg.timestamp = 10

encoded = encoded_t()
encoded.msg = ZCM.encode(msg)
encoded.n   = length(encoded.msg)

decoded = ZCM.decode(example_t, encoded.msg)
@assert (decoded.timestamp == msg.timestamp) "Encode/decode mismatch"

println("Success!")
