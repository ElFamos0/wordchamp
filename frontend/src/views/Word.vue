<template>
  <div class="random">
    <h1>Venez jouer à WordChamp</h1>
    <GetWord />
    <b-container>
      <KeyBoard/>
    </b-container>
  </div>
</template>

<script>

import GetWord from '@/components/GetWord.vue';
import KeyBoard from '@/components/KeyBoard.vue';

export default {
  name: 'word-page',
  components: {
    GetWord,
    KeyBoard,
  },
};
</script>