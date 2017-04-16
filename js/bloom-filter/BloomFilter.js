(function (exports) {
    exports.BloomFilter = BloomFilter;

    function BloomFilter(storageSize, hashCount, seed) {
        this.storageSize = storageSize;
        this.storage = new Uint32Array(Math.ceil(storageSize / 32));
        this.hashCount = hashCount;
        this.seed = (seed === undefined) ? 0x1c981dc5 : seed;
        this._hashResult = new Uint32Array(hashCount);
    }

    BloomFilter.prototype.hashes = function (v) {
        var result = this._hashResult,
            m = this.storageSize;
        var a = fnv(v + "", this.seed) % m,
            b = fnv(v + "") % m;

        for (var i = 0, c = this.hashCount; i < c; ++i) {
            result[i] = a >= 0 ? a : a + m;
            a = (a + b) % m;
        }

        return result;
    };

    BloomFilter.prototype.add = function (v) {
        this.hashes(v).forEach(function (h) {
            this.storage[Math.floor(h / 32)] |= 1 << (h % 32);
        }, this);
    };

    BloomFilter.prototype.test = function (v) {
        return this.hashes(v).every(function (h) {
            return (this.storage[Math.floor(h / 32)] & (1 << (h % 32))) !== 0;
        }, this);
    };

    /**
     * 32 bit FNV-1a hash
     * Ref.: http://isthe.com/chongo/tech/comp/fnv/
     *
     * @param {string} str the input value
     * @param {int} [seed] optionally pass the hash seed
     * @return {int}
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
