(function (exports) {
    exports.BloomFilter = BloomFilter;

    /**
     * Bloom filter constructor
     *
     * @param {int} size filter size in bits
     * @param {int} hashCount count of hash functions
     * @param {int} [seed] optionally passed seed for hashing
     * @constructor
     */
    function BloomFilter(size, hashCount, seed) {
        this.size = size;
        this.hashCount = hashCount;
        this.seed = (seed === undefined) ? 0x1c981dc7 : seed;
        this.storage = new Uint32Array(Math.ceil(size / 32));
        this._hashResult = new Uint32Array(hashCount);
    }

    /**
     * Generate hashCount hash values for given key
     *
     * @param {string|*} key value for hashing
     * @returns {Uint32Array} array of hashCount values in [0 ... size-1] range
     */
    BloomFilter.prototype.hash = function (key) {
        var result = this._hashResult,
            m = this.size;
        var a = fnv(key + "") % m,
            b = fnv(key + "", this.seed);

        for (var i = 0, c = this.hashCount; i < c; ++i) {
            result[i] = ((a + b * i) >>> 0) % m;
        }

        return result;
    };

    /**
     * Adds given key to set
     *
     * @param {string|*} key
     */
    BloomFilter.prototype.add = function (key) {
        this.hash(key).forEach(function (h) {
            this.storage[Math.floor(h / 32)] |= 1 << (h % 32);
        }, this);
    };

    /**
     * Tests that given key is in set
     *
     * @param {string|*} key
     * @returns {boolean} false <=> key is not in set, true <=> key probably is in set
     */
    BloomFilter.prototype.test = function (key) {
        return this.hash(key).every(function (h) {
            return (this.storage[Math.floor(h / 32)] & (1 << (h % 32))) !== 0;
        }, this);
    };

    /**
     * 32 bit FNV-1a hash
     * Ref.: http://isthe.com/chongo/tech/comp/fnv/
     *
     * @param {string} str the input value
     * @param {int} [seed] optionally pass the hash seed
     * @returns {int}
     */
    function fnv(str, seed) {
        var i, l;
        var hash = (seed === undefined) ? 0x811c9dc5 : seed;

        for (i = 0, l = str.length; i < l; i++) {
            hash ^= str.charCodeAt(i);
            hash += (hash << 1) + (hash << 4) + (hash << 7) + (hash << 8) + (hash << 24);
        }

        return hash >>> 0;
    }
})(typeof exports !== "undefined" ? exports : this);
