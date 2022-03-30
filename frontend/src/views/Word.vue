<template>
  <div class="random">
    <h1>Venez jouer à WordChamp</h1>
    <GetWord />
  </div>
</template>

<script>

import GetWord from '@/components/GetWord.vue';

export default {
  name: 'Word',
  components: {
    GetWord,
  },
};
</script>
