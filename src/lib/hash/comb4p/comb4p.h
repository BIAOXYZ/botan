/*
* Comb4P hash combiner
* (C) 2010 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#ifndef BOTAN_COMB4P_H__
#define BOTAN_COMB4P_H__

#include <botan/hash.h>

namespace Botan {

/**
* Combines two hash functions using a Feistel scheme. Described in
* "On the Security of Hash Function Combiners", Anja Lehmann
*/
class BOTAN_DLL Comb4P final : public HashFunction
   {
   public:
      /**
      * @param h1 the first hash
      * @param h2 the second hash
      */
      Comb4P(HashFunction* h1, HashFunction* h2);

      size_t hash_block_size() const override;

      size_t output_length() const override
         {
         return m_hash1->output_length() + m_hash2->output_length();
         }

      HashFunction* clone() const override
         {
         return new Comb4P(m_hash1->clone(), m_hash2->clone());
         }

      std::string name() const override
         {
         return "Comb4P(" + m_hash1->name() + "," + m_hash2->name() + ")";
         }

      void clear() override;
   private:
      void add_data(const byte input[], size_t length) override;
      void final_result(byte out[]) override;

      std::unique_ptr<HashFunction> m_hash1, m_hash2;
   };

}

#endif