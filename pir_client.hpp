#pragma once

#include "pir.hpp"
#include <memory>

class PIRClient {
  public:
    PIRClient(const seal::EncryptionParameters &parms,
              const seal::EncryptionParameters &expandedParams, const PirParams &pirparms);

    void update_parameters(const seal::EncryptionParameters &expandedParams,
                           const PirParams &pirparms);

    PirQuery generate_query(std::uint64_t desiredIndex);
    seal::Plaintext decode_reply(PirReply reply);

    seal::GaloisKeys generate_galois_keys();

    // Index and offset of an element in an FV plaintext
    uint64_t get_fv_index(uint64_t element_idx, uint64_t ele_size);
    uint64_t get_fv_offset(uint64_t element_idx, uint64_t ele_size);

  private:
    // Should we store a decryptor and an encryptor?
    seal::EncryptionParameters params_;
    seal::EncryptionParameters expanded_params_;
    PirParams pir_params_;

    std::unique_ptr<seal::Encryptor> encryptor_;
    std::unique_ptr<seal::Decryptor> decryptor_;
    std::unique_ptr<seal::Evaluator> evaluator_;
    std::unique_ptr<seal::KeyGenerator> keygen_;

    seal::Ciphertext compose_to_ciphertext(std::vector<seal::Plaintext> plains);
};
