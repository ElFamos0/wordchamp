<template>
    <!-- id inutile ? -->
    <div @dblclick="$emit('show-details', entryId )" class="entryContainer" :style="colorClass">
        <div>(Id de la partie : {{entryId}})</div>
        <!-- <div>Solution : {{solution}}</div> -->
        <WordRow :solution="solution" :word="solution" submitted="true"/>
        <div>{{result}}</div>
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
      let color = (this.result == 'Victoire' ) ? '#60b760' : '#ff4545';
      return 'background-color: '+color;
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
  margin: 20px 50px auto;
  overflow: auto;
  /* border: 1px solid rgb(145, 145, 145); */
  padding: 10px;
  border-radius: 5px;
  background: rgb(205, 205, 205);
}
</style>