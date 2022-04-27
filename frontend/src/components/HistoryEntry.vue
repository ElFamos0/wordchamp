<template>
    <div @dblclick="$emit('show-details', entryId )" class="entryContainer" :style="colorClass">
      <!-- <div>(Id de la partie : {{entryId}})</div> -->
      <div style="font-family: 'Roboto', sans-serif;font-size: 3em; max-width: 0px; padding-left: 7%">{{result}}</div>
      <WordRow :solution="solution" :word="solution" :submitted="false" style="padding-left: 53%; padding-top: 0.7%; max-width: 100%"/>
    </div>
</template>


<script>
import WordRow from './WordRow.vue'
export default {
  name: 'HistoryEntry',
  props: {
    entryId : String,
    solution : String,
    result: String,
  },
  computed: {
    colorClass() {
      console.log(this.result)
      let color1 = (this.result == 'Victoire' ) ? 'green' : 'red';
      let color2 = (this.result == 'Victoire' ) ? 'rgb(118, 255, 127)' : 'rgb(255, 134, 134)';

      return 'box-shadow: rgba(0, 0, 0, 0.2) 0px 12px 28px 0px, rgba(0, 0, 0, 0.1) 0px 2px 4px 0px, rgba(255, 255, 255, 0.05) 0px 0px 0px 1px inset; background:linear-gradient('+color1+', transparent),linear-gradient(to top left, '+color2+', transparent);background-blend-mode: screen;'
    }
  },
  components: {
    WordRow
  },
  emits: ['show-details'],
}
</script>


<style scoped>

.entryContainer {
  margin: 20px 20% auto;
  overflow: auto;
  /* border: 1px solid rgb(145, 145, 145); */
  padding: 10px;
  border-radius: 5px;
  background: rgb(205, 205, 205);
  display: flex;
}
</style>